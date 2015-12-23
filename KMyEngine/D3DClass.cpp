////////////////////////////////////////////////////////////////////////////////
// Filename: d3dclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "d3dclass.h"


D3DClass::D3DClass()
{
	m_swapChain = 0;
	m_device = 0;
	m_deviceContext = 0;
	m_depthStencilView = 0;
	m_renderTargetView = 0;
	m_depthStencilView = 0;
	m_depthStencilBuffer = 0;
}


D3DClass::D3DClass(const D3DClass& other)
{
}


D3DClass::~D3DClass()
{
}


bool D3DClass::Initialize(int screenWidth, int screenHeight, bool vsync, HWND hwnd, bool fullscreen)
{
	//---------------------------------------------------------------------------------------
	// 1.创建设备及设备上下文 
	//---------------------------------------------------------------------------------------
	UINT createDeviceFlag = 0;
	md3dDriverType = D3D_DRIVER_TYPE_HARDWARE;
	mEnable4xMsaa = true;
	m_vsync_enabled = true;

#if defined(DEBUG) || defined(_DEBUG)
	createDeviceFlag |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	D3D_FEATURE_LEVEL featureLevel;
	HRESULT hr = D3D11CreateDevice(0,md3dDriverType,0,createDeviceFlag,0, 0,D3D11_SDK_VERSION,&m_device,&featureLevel,&m_deviceContext);

	if (FAILED(hr))
	{
		MessageBox(0, L"D3D11CreateDevice Failed.", 0, 0);
		return false;
	}
	if (featureLevel != D3D_FEATURE_LEVEL_11_0)
	{
		MessageBox(0, L"Direct3D Feature Level 11 unsupported.", 0, 0);
		return false;
	}

	// 为后缓冲区格式检查是否支持4倍抗锯齿。 所有支持DX11的设备都支持4X MSAA ，所以这里只需要检查是否支持4倍即可
	m_device->CheckMultisampleQualityLevels(DXGI_FORMAT_R8G8B8A8_UNORM, 4, &m4xMsaaQuality);
	assert(m4xMsaaQuality > 0);

	//---------------------------------------------------------------------------------------
	//  
	//---------------------------------------------------------------------------------------
	//填充交换链描述结构体
	DXGI_SWAP_CHAIN_DESC sd;
	sd.BufferDesc.Width = screenWidth;
	sd.BufferDesc.Height = screenHeight;
	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

	if (mEnable4xMsaa)
	{
		sd.SampleDesc.Count = 4;
		sd.SampleDesc.Quality = m4xMsaaQuality -1;
	}
	else
	{
		sd.SampleDesc.Count = 1;
		sd.SampleDesc.Quality = 0;
	}
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.BufferCount = 1;
	sd.OutputWindow = hwnd;
	sd.Windowed = true;
	sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	sd.Flags = 0;

	// 为了正确的创建交换链，我们必须使用IDXGIFactory，如果我们用成了另外一个CreateDXGIFactory，将会报错

	IDXGIDevice* dxgiDevice = NULL;
	HR(m_device->QueryInterface(__uuidof(IDXGIDevice), (void**)&dxgiDevice));

	IDXGIAdapter* dxgiAdapter = NULL;
	HR(dxgiDevice->GetParent(__uuidof(IDXGIAdapter), (void**)&dxgiAdapter));

	IDXGIFactory* dxgiFactory = NULL;
	HR(dxgiAdapter->GetParent(__uuidof(IDXGIFactory), (void**)&dxgiFactory));

	HR(dxgiFactory->CreateSwapChain(m_device, &sd, &m_swapChain));

	ReleaseCOM(dxgiDevice);
	ReleaseCOM(dxgiAdapter);
	ReleaseCOM(dxgiFactory);

	OnResize(screenWidth,screenHeight);	


	D3D11_DEPTH_STENCIL_DESC depthDisabledStencilDesc;
	depthDisabledStencilDesc.DepthEnable = false;
	depthDisabledStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	depthDisabledStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;
	depthDisabledStencilDesc.StencilEnable = true;
	depthDisabledStencilDesc.StencilReadMask = 0xFF;
	depthDisabledStencilDesc.StencilWriteMask = 0xFF;
	depthDisabledStencilDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthDisabledStencilDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
	depthDisabledStencilDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthDisabledStencilDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
	depthDisabledStencilDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthDisabledStencilDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
	depthDisabledStencilDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthDisabledStencilDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	HR(m_device->CreateDepthStencilState(&depthDisabledStencilDesc, &m_depthDisabledStencilState));

	D3D11_DEPTH_STENCIL_DESC depthStencilDesc;
	depthStencilDesc.DepthEnable = true;
	depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;

	depthStencilDesc.StencilEnable = true;
	depthStencilDesc.StencilReadMask = 0xFF;
	depthStencilDesc.StencilWriteMask = 0xFF;

	// Stencil operations if pixel is front-facing.
	depthStencilDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
	depthStencilDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	// Stencil operations if pixel is back-facing.
	depthStencilDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
	depthStencilDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	HR(m_device->CreateDepthStencilState(&depthStencilDesc, &m_depthStencilState));

	return true;
}

bool D3DClass::OnResize(int width,int height)
{
	m_clientHeight = height;
	m_clientWidth = width;

	//---------------------------------------------------------------------------------------
	// Release the old views, as they hold references to the buffers we will be destroying.  Also release the old depth/stencil buffer.
	// 1.释放旧的各个视图
	//---------------------------------------------------------------------------------------
	ReleaseCOM(m_renderTargetView);
	ReleaseCOM(m_depthStencilView);
	ReleaseCOM(m_depthStencilBuffer);

	//---------------------------------------------------------------------------------------
	// Resize the swap chain and recreate the render target view.
	// 2.重新设置交换链的大小和渲染目标视图
	//---------------------------------------------------------------------------------------
	HR(m_swapChain->ResizeBuffers(1, width, height, DXGI_FORMAT_R8G8B8A8_UNORM, 0));
	ID3D11Texture2D* backBuffer;
	HR(m_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&backBuffer)));
	HR(m_device->CreateRenderTargetView(backBuffer, 0, &m_renderTargetView));
	ReleaseCOM(backBuffer);


	//---------------------------------------------------------------------------------------
	// Create the depth/stencil buffer and view.
	// 3.创建深度模板缓存和其视图 : 描述结构体要完全填充！
	//---------------------------------------------------------------------------------------
	D3D11_TEXTURE2D_DESC depthStencilDes;
	depthStencilDes.Width = width;
	depthStencilDes.Height = height;
	depthStencilDes.MipLevels = 1;
	depthStencilDes.ArraySize = 1;
	depthStencilDes.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;

	// Use 4X MSAA? --must match swap chain MSAA values.
	// 这里的多重采样抗锯齿要和交换链中的一致
	if (mEnable4xMsaa)
	{
		depthStencilDes.SampleDesc.Count = 4;
		depthStencilDes.SampleDesc.Quality = m4xMsaaQuality - 1;
	}
	else
	{
		depthStencilDes.SampleDesc.Count = 1;
		depthStencilDes.SampleDesc.Quality = 0;
	}
	depthStencilDes.Usage = D3D11_USAGE_DEFAULT;
	depthStencilDes.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthStencilDes.CPUAccessFlags = 0;
	depthStencilDes.MiscFlags = 0;

	HR(m_device->CreateTexture2D(&depthStencilDes, 0, &m_depthStencilBuffer));
	HR(m_device->CreateDepthStencilView(m_depthStencilBuffer, 0, &m_depthStencilView));

	//---------------------------------------------------------------------------------------
	//  Bind the render target view and depth/stencil view to the pipeline.
	//  4.绑定渲染目标视图、深度模板视图 绑定到管线 : 这里有很多参考学习的地方！比如说这里有多个视图？
	//---------------------------------------------------------------------------------------
	m_deviceContext->OMSetRenderTargets(1, &m_renderTargetView, m_depthStencilView);


	//---------------------------------------------------------------------------------------
	//  Set the viewport transform.  
	//  5.设置视口变换 : 完全填充结构体S
	//---------------------------------------------------------------------------------------

	mScreenViewport.TopLeftX = 0;
	mScreenViewport.TopLeftY = 0;
	mScreenViewport.Width = static_cast<float>(width);
	mScreenViewport.Height = static_cast<float>(height);
	mScreenViewport.MinDepth = 0.0f;
	mScreenViewport.MaxDepth = 1.0f;

	m_deviceContext->RSSetViewports(1, &mScreenViewport);	

	return true;
}

void D3DClass::Shutdown()
{
	ReleaseCOM(m_swapChain);
	ReleaseCOM(m_device);
	ReleaseCOM(m_deviceContext);

	ReleaseCOM(m_renderTargetView);
	ReleaseCOM(m_depthStencilBuffer);
	ReleaseCOM(m_depthStencilView);

	ReleaseCOM(m_depthStencilState);
	ReleaseCOM(m_depthDisabledStencilState);
	
	return;
}


void D3DClass::BeginScene(float red, float green, float blue, float alpha)
{
	float color[4];

	color[0] = red;
	color[1] = green;
	color[2] = blue;
	color[3] = alpha;

	m_deviceContext->ClearRenderTargetView(m_renderTargetView, color);
	m_deviceContext->ClearDepthStencilView(m_depthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);

	return;
}


void D3DClass::EndScene()
{
	if(m_vsync_enabled)
	{
		// Lock to screen refresh rate.
		m_swapChain->Present(1, 0);
	}
	else
	{
		// Present as fast as possible.
		m_swapChain->Present(0, 0);
	}

	return;
}


ID3D11Device* D3DClass::GetDevice()
{
	return m_device;
}


ID3D11DeviceContext* D3DClass::GetDeviceContext()
{
	return m_deviceContext;
}

float D3DClass::GetAspectRatio()
{
	return static_cast<float>(m_clientWidth) / (m_clientHeight);
}

int D3DClass::GetClientWidth()
{
	return m_clientWidth;
}
int D3DClass::GetClientHeight()
{
	return m_clientHeight;
}


void D3DClass::TurnZBufferOn()
{
	m_deviceContext->OMSetDepthStencilState(m_depthStencilState, 1);
	return;
}


void D3DClass::TurnZBufferOff()
{
	m_deviceContext->OMSetDepthStencilState(m_depthDisabledStencilState, 1);
	return;
}

void D3DClass::SetBackBufferRenderTarget()
{
	m_deviceContext->OMSetRenderTargets(1, &m_renderTargetView, m_depthStencilView);

	return;
}

void D3DClass::ResetViewport()
{
	m_deviceContext->RSSetViewports(1, &mScreenViewport);

	return;
}