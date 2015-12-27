////////////////////////////////////////////////////////////////////////////////
// Filename: deferredbuffersclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "deferredbuffersclass.h"


DeferredBuffersClass::DeferredBuffersClass()
{
	int i;

	for(i=0; i<BUFFER_COUNT; i++)
	{
		m_renderTargetTextureArray[i] = 0;
		m_renderTargetViewArray[i] = 0;
		m_shaderResourceViewArray[i] = 0;
	}

	m_depthStencilBuffer = 0;
	m_depthStencilView = 0;
}


DeferredBuffersClass::DeferredBuffersClass(const DeferredBuffersClass& other)
{
}


DeferredBuffersClass::~DeferredBuffersClass()
{
}


bool DeferredBuffersClass::Initialize(ID3D11Device* device, int textureWidth, int textureHeight)
{
	D3D11_TEXTURE2D_DESC textureDesc;
	HRESULT result;
	D3D11_RENDER_TARGET_VIEW_DESC renderTargetViewDesc;
	D3D11_SHADER_RESOURCE_VIEW_DESC shaderResourceViewDesc;
	D3D11_TEXTURE2D_DESC depthBufferDesc;
	D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc;
	int i;


	m_textureWidth = textureWidth;
	m_textureHeight = textureHeight;

	ZeroMemory(&textureDesc, sizeof(textureDesc));

	textureDesc.Width = textureWidth;
	textureDesc.Height = textureHeight;
	textureDesc.MipLevels = 1;
	textureDesc.ArraySize = 1;
	textureDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	textureDesc.SampleDesc.Count = 1;
	textureDesc.Usage = D3D11_USAGE_DEFAULT;
	textureDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
	textureDesc.CPUAccessFlags = 0;
    textureDesc.MiscFlags = 0;

	for(i=0; i<BUFFER_COUNT; i++)
	{
		HR(device->CreateTexture2D(&textureDesc, NULL, &m_renderTargetTextureArray[i]));
	}
	HR(device->CreateTexture2D(&textureDesc, NULL, &m_FinalColorTexture));
	HR(device->CreateTexture2D(&textureDesc, NULL, &m_FinalColorTextureAA));
	HR(device->CreateTexture2D(&textureDesc, NULL, &m_BloomTextureArray[0]));
	HR(device->CreateTexture2D(&textureDesc, NULL, &m_BloomTextureArray[1]));


	renderTargetViewDesc.Format = textureDesc.Format;
	renderTargetViewDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
	renderTargetViewDesc.Texture2D.MipSlice = 0;

	for(i=0; i<BUFFER_COUNT; i++)
	{
		HR(device->CreateRenderTargetView(m_renderTargetTextureArray[i], &renderTargetViewDesc, &m_renderTargetViewArray[i]));
	}
	HR(device->CreateRenderTargetView(m_FinalColorTexture, &renderTargetViewDesc, &m_FinalColorRTV));
	HR(device->CreateRenderTargetView(m_FinalColorTextureAA, &renderTargetViewDesc, &m_FinalColorAARTV));
	HR(device->CreateRenderTargetView(m_BloomTextureArray[0], &renderTargetViewDesc, &m_BloomRTVArray[0]));
	HR(device->CreateRenderTargetView(m_BloomTextureArray[1], &renderTargetViewDesc, &m_BloomRTVArray[1]));


	shaderResourceViewDesc.Format = textureDesc.Format;
	shaderResourceViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	shaderResourceViewDesc.Texture2D.MostDetailedMip = 0;
	shaderResourceViewDesc.Texture2D.MipLevels = 1;

	for(i=0; i<BUFFER_COUNT; i++)
	{
		HR(device->CreateShaderResourceView(m_renderTargetTextureArray[i], &shaderResourceViewDesc, &m_shaderResourceViewArray[i]));
	}
	HR(device->CreateShaderResourceView(m_FinalColorTexture, &shaderResourceViewDesc, &m_FinalColorSRV));
	HR(device->CreateShaderResourceView(m_FinalColorTextureAA, &shaderResourceViewDesc, &m_FinalColorAASRV));
	HR(device->CreateShaderResourceView(m_BloomTextureArray[0], &shaderResourceViewDesc, &m_BloomSRVArray[0]));
	HR(device->CreateShaderResourceView(m_BloomTextureArray[1], &shaderResourceViewDesc, &m_BloomSRVArray[1]));

	ZeroMemory(&depthBufferDesc, sizeof(depthBufferDesc));

	depthBufferDesc.Width = textureWidth;
	depthBufferDesc.Height = textureHeight;
	depthBufferDesc.MipLevels = 1;
	depthBufferDesc.ArraySize = 1;
	depthBufferDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthBufferDesc.SampleDesc.Count = 1;
	depthBufferDesc.SampleDesc.Quality = 0;
	depthBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	depthBufferDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthBufferDesc.CPUAccessFlags = 0;
	depthBufferDesc.MiscFlags = 0;

	result = device->CreateTexture2D(&depthBufferDesc, NULL, &m_depthStencilBuffer);
	if(FAILED(result))
	{
		return false;
	}

	ZeroMemory(&depthStencilViewDesc, sizeof(depthStencilViewDesc));

	depthStencilViewDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	depthStencilViewDesc.Texture2D.MipSlice = 0;

	result = device->CreateDepthStencilView(m_depthStencilBuffer, &depthStencilViewDesc, &m_depthStencilView);
	if(FAILED(result))
	{
		return false;
	}

    m_viewport.Width = (float)textureWidth;
    m_viewport.Height = (float)textureHeight;
    m_viewport.MinDepth = 0.0f;
    m_viewport.MaxDepth = 1.0f;
    m_viewport.TopLeftX = 0.0f;
    m_viewport.TopLeftY = 0.0f;

	return true;
}


void DeferredBuffersClass::Shutdown()
{
	ReleaseCOM(m_depthStencilView);
	ReleaseCOM(m_depthStencilBuffer);

	for(int i=0; i<BUFFER_COUNT; i++)
	{
		ReleaseCOM(m_shaderResourceViewArray[i]);
		ReleaseCOM(m_renderTargetViewArray[i]);
		ReleaseCOM(m_renderTargetTextureArray[i]);
	}

	ReleaseCOM(m_FinalColorTexture);
	ReleaseCOM(m_FinalColorRTV);
	ReleaseCOM(m_FinalColorSRV);

	ReleaseCOM(m_FinalColorTextureAA);
	ReleaseCOM(m_FinalColorAARTV);
	ReleaseCOM(m_FinalColorAASRV);

	for(int i=0; i<2; i++)
	{
		ReleaseCOM(m_BloomRTVArray[i]);
		ReleaseCOM(m_BloomSRVArray[i]);
		ReleaseCOM(m_BloomTextureArray[i]);
	}

	return;
}


void DeferredBuffersClass::SetRenderTargets(ID3D11DeviceContext* deviceContext)
{
	// Bind the render target view array and depth stencil buffer to the output render pipeline.
	deviceContext->OMSetRenderTargets(BUFFER_COUNT, m_renderTargetViewArray, m_depthStencilView);
	
	deviceContext->RSSetViewports(1, &m_viewport);
	
	return;
}
void DeferredBuffersClass::ClearRenderTargets(ID3D11DeviceContext* deviceContext, float red, float green, float blue, float alpha)
{
	float color[4];
	int i;

	color[0] = red;
	color[1] = green;
	color[2] = blue;
	color[3] = alpha;

	for(i=0; i<BUFFER_COUNT; i++)
	{
		deviceContext->ClearRenderTargetView(m_renderTargetViewArray[i], color);
	}

	deviceContext->ClearDepthStencilView(m_depthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);

	return;
}
ID3D11ShaderResourceView* DeferredBuffersClass::GetShaderResourceView(int view)
{
	return m_shaderResourceViewArray[view];
}

bool DeferredBuffersClass::OnResize(ID3D11Device* pd,int width,int height)
{
	Shutdown();

	Initialize(pd,width,height);
	

	return true;
}

int DeferredBuffersClass::GetTextureWidth()
{
	return m_textureWidth;
}

int DeferredBuffersClass::GetTextureHeight()
{
	return m_textureHeight;
}

void DeferredBuffersClass::SetLightingRenderTarget(ID3D11DeviceContext* deviceContext)
{
	deviceContext->OMSetRenderTargets(1, &m_FinalColorRTV, m_depthStencilView);

	deviceContext->RSSetViewports(1, &m_viewport);

	return;
}
void DeferredBuffersClass::ClearLightingRenderTargets(ID3D11DeviceContext* deviceContext, float red, float green, float blue, float alpha)
{
	float color[4];
	int i;

	color[0] = red;
	color[1] = green;
	color[2] = blue;
	color[3] = alpha;

	/*for(i=0; i<BUFFER_COUNT; i++)
	{
	deviceContext->ClearRenderTargetView(m_renderTargetViewArray[i], color);
	}*/

	deviceContext->ClearRenderTargetView(m_FinalColorRTV, color);
	deviceContext->ClearDepthStencilView(m_depthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);

	return;
}
ID3D11ShaderResourceView* DeferredBuffersClass::GetLightingSRV()
{
	return m_FinalColorSRV;
}

void DeferredBuffersClass::SetEdgeDetectAARenderTarget(ID3D11DeviceContext* deviceContext)
{
	deviceContext->OMSetRenderTargets(1, &m_FinalColorAARTV, m_depthStencilView);

	deviceContext->RSSetViewports(1, &m_viewport);

	return;
}
void DeferredBuffersClass::ClearEdgeDetectAARenderTargets(ID3D11DeviceContext* deviceContext, float red, float green, float blue, float alpha)
{
	float color[4];
	int i;

	color[0] = red;
	color[1] = green;
	color[2] = blue;
	color[3] = alpha;

	/*for(i=0; i<BUFFER_COUNT; i++)
	{
	deviceContext->ClearRenderTargetView(m_renderTargetViewArray[i], color);
	}*/

	deviceContext->ClearRenderTargetView(m_FinalColorAARTV, color);
	deviceContext->ClearDepthStencilView(m_depthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);

	return;
}
ID3D11ShaderResourceView* DeferredBuffersClass::GetEdgeDetectAASRV()
{
	return m_FinalColorAASRV;
}

void DeferredBuffersClass::SetBloomRenderTargets(ID3D11DeviceContext* deviceContext)
{
	// Bind the render target view array and depth stencil buffer to the output render pipeline.
	deviceContext->OMSetRenderTargets(2, m_BloomRTVArray, m_depthStencilView);

	deviceContext->RSSetViewports(1, &m_viewport);

	return;
}
void DeferredBuffersClass::ClearBloomRenderTargets(ID3D11DeviceContext* deviceContext, float red, float green, float blue, float alpha)
{
	float color[4];
	int i;

	color[0] = red;
	color[1] = green;
	color[2] = blue;
	color[3] = alpha;

	for(i=0; i<2; i++)
	{
		deviceContext->ClearRenderTargetView(m_BloomRTVArray[i], color);
	}

	deviceContext->ClearDepthStencilView(m_depthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);

	return;
}
ID3D11ShaderResourceView* DeferredBuffersClass::GetBloomShaderResourceView(int view)
{
	return m_BloomSRVArray[view];
}