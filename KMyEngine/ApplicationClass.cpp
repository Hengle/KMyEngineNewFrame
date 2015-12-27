////////////////////////////////////////////////////////////////////////////////
// Filename: graphicsclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "ApplicationClass.h"


CApplicationClass::CApplicationClass()
{
	m_D3D = 0;
	//m_Input = 0;
	m_ShaderManager = 0;
	m_Light = 0;
	m_Camera = 0;
	m_Model1 = 0;
	m_Model2 = 0;
	m_Model3 = 0;
}


CApplicationClass::CApplicationClass(const CApplicationClass& other)
{
}


CApplicationClass::~CApplicationClass()
{
}

bool CApplicationClass::InitD3D(int width, int heitht, HWND outputWindow,HINSTANCE hinstance)
{
	Initialize(width,heitht,outputWindow,hinstance);

	return true;
}

bool CApplicationClass::DrawScene()
{
	Render();

	Frame();
	return true;
}

bool CApplicationClass::Initialize(int screenWidth, int screenHeight, HWND hwnd,HINSTANCE hinstance)
{
	bool result;

	m_D3D = new D3DClass;
	if(!m_D3D)
	{
		return false;
	}
	result = m_D3D->Initialize(screenWidth, screenHeight, VSYNC_ENABLED, hwnd, FULL_SCREEN);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize Direct3D.", L"Error", MB_OK);
		return false;
	}

	/*m_Input = new InputClass;
	result = m_Input->Initialize(hinstance,hwnd,screenWidth,screenHeight);
	if(!result)
	{
	MessageBox(hwnd, L"Could not initialize the input object.", L"Error", MB_OK);
	return false;
	}*/

	m_ShaderManager = new ShaderManagerClass;
	if(!m_ShaderManager)
	{
		return false;
	}

	result = m_ShaderManager->Initialize(m_D3D->GetDevice(), hwnd);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the shader manager object.", L"Error", MB_OK);
		return false;
	}

	m_Camera = new CCameraClass;
	if(!m_Camera)
	{
		return false;
	}
	m_Camera->Init();


	m_Light = new LightClass;
	if(!m_Light)
	{
		return false;
	}

	m_Light->SetAmbientColor(0.15f, 0.15f, 0.15f, 1.0f);
	m_Light->SetDiffuseColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_Light->SetDirection(0.0f, 0.0f, 1.0f);
	m_Light->SetSpecularColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_Light->SetSpecularPower(64.0f);

	m_Model1 = new ModelClass;
	if(!m_Model1)
	{
		return false;
	}

	result = m_Model1->Initialize(m_D3D->GetDevice(), "../KMyEngineData/data/cube.txt", L"../KMyEngineData/data/marble.dds");
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the first model object.", L"Error", MB_OK);
		return false;
	}

	m_Model2 = new ModelClass;
	if(!m_Model2)
	{
		return false;
	}

	result = m_Model2->Initialize(m_D3D->GetDevice(), "../KMyEngineData/data/cube.txt", L"../KMyEngineData/data/metal.dds");
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the second model object.", L"Error", MB_OK);
		return false;
	}

	m_Model3 = new BumpModelClass;
	if(!m_Model3)
	{
		return false;
	}

	result = m_Model3->Initialize(m_D3D->GetDevice(), "../KMyEngineData/data/cube.txt", L"../KMyEngineData/data/stone.dds", 
		L"../KMyEngineData/data/normal.dds");
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the third model object.", L"Error", MB_OK);
		return false;
	}

	m_dsBufferClass.Initialize(m_D3D->GetDevice(),m_D3D->GetClientWidth(),m_D3D->GetClientHeight());
	m_orthoWindowClass.Initialize(m_D3D->GetDevice(),m_D3D->GetClientWidth(),m_D3D->GetClientHeight());

	isNotFirst = false;

	return true;
}

bool CApplicationClass::OnResize(int width, int height)
{
	m_D3D->OnResize(width,height);
	m_dsBufferClass.OnResize(m_D3D->GetDevice(),width,height);
	m_Camera->SetLens(0.25f*CMathHelper::Pi, m_D3D->GetAspectRatio(), 1.0f, 1000.0f);

	return true;
}

void CApplicationClass::Shutdown()
{
	if(m_Model1)
	{
		m_Model1->Shutdown();
		delete m_Model1;
		m_Model1 = 0;
	}

	if(m_Model2)
	{
		m_Model2->Shutdown();
		delete m_Model2;
		m_Model2 = 0;
	}

	if(m_Model3)
	{
		m_Model3->Shutdown();
		delete m_Model3;
		m_Model3 = 0;
	}

	if(m_Light)
	{
		delete m_Light;
		m_Light = 0;
	}

	if(m_Camera)
	{
		delete m_Camera;
		m_Camera = 0;
	}

	if(m_ShaderManager)
	{
		m_ShaderManager->Shutdown();
		delete m_ShaderManager;
		m_ShaderManager = 0;
	}

	m_dsBufferClass.Shutdown();
	m_orthoWindowClass.Shutdown();

	if(m_D3D)
	{
		m_D3D->Shutdown();
		delete m_D3D;
		m_D3D = 0;
	}


	return;
}


bool CApplicationClass::Frame()
{
	bool result;

	m_Camera->UpdateViewMatrix();

	return true;
}


bool CApplicationClass::Render()
{
	//RenderMultiShaderTest();

	RenderDeferredShadingTest();

	return true;
}

bool CApplicationClass::RenderMultiShaderTest()
{
	XMMATRIX worldMatrix, viewMatrix, projectionMatrix, translateMatrix;
	bool result;

	m_D3D->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);

	worldMatrix = XMMatrixIdentity();
	viewMatrix = m_Camera->View();
	projectionMatrix = m_Camera->ViewProj();

	translateMatrix = XMMatrixTranslation(-3.5f,0.0f,0.0f);
	worldMatrix = XMMatrixMultiply(worldMatrix,translateMatrix);

	m_Model1->Render(m_D3D->GetDeviceContext());
	result = m_ShaderManager->RenderTextureShader(m_D3D->GetDeviceContext(), m_Model1->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, 
		m_Model1->GetTexture());
	if(!result)
	{
		return false;
	}

	worldMatrix = XMMatrixIdentity();
	translateMatrix = XMMatrixTranslation( 0.0f, 0.0f, 0.0f);
	worldMatrix = XMMatrixMultiply(worldMatrix,translateMatrix);

	m_Model2->Render(m_D3D->GetDeviceContext());
	result = m_ShaderManager->RenderLightShader(m_D3D->GetDeviceContext(), m_Model2->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, 
		m_Model2->GetTexture(), m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(), 
		m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
	if(!result)
	{
		return false;
	}

	worldMatrix = XMMatrixIdentity();
	translateMatrix = XMMatrixTranslation(3.5f,0.0f,0.0f);
	worldMatrix = XMMatrixMultiply(worldMatrix,translateMatrix);

	m_Model3->Render(m_D3D->GetDeviceContext());
	result = m_ShaderManager->RenderBumpMapShader(m_D3D->GetDeviceContext(), m_Model3->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, 
		m_Model3->GetColorTexture(), m_Model3->GetNormalMapTexture(), m_Light->GetDirection(), 
		m_Light->GetDiffuseColor());
	if(!result)
	{
		return false;
	}

	m_D3D->EndScene();

	return true;
}

void CApplicationClass::OnMouseDown(int type, int x, int y)
{
	mLastMousePos.x = x;
	mLastMousePos.y = y;
}

void CApplicationClass::OnMouseMove(int type, int x, int y)
{
	if (type == 0)
	{
		float dx = XMConvertToRadians(0.25f*static_cast<float>(x - mLastMousePos.x));
		float dy = XMConvertToRadians(0.25f*static_cast<float>(y - mLastMousePos.y));

		m_Camera->RotateY(dx);
		m_Camera->Pitch(dy);
	}

	mLastMousePos.x = x;
	mLastMousePos.y = y;
}

void CApplicationClass::KeyInput(char keycode)
{
	float speed = 0.01f;

	if (keycode == 'w')
	{
		m_Camera->Walk(10.0f * speed);
	}
	if (keycode == 's')
	{
		m_Camera->Walk(-10.0f * speed);
	}
	if (keycode == 'a')
	{
		m_Camera->Strafe(-10.0f * speed);
	}
	if (keycode == 'd')
	{
		m_Camera->Strafe(10.0f * speed);
	}

	Frame();

}

bool CApplicationClass::RenderDeferredShadingTest()
{
	bool result;
	
	XMMATRIX worldMatrix, viewMatrix, projectionMatrix;
	ShaderMatrix shaderMatrix;

	XMStoreFloat4x4(&shaderMatrix.gWorld,XMMatrixIdentity());
	XMStoreFloat4x4(&shaderMatrix.gView,m_Camera->View());
	XMStoreFloat4x4(&shaderMatrix.gProj,m_Camera->Proj());


	m_Model2->Render(m_D3D->GetDeviceContext());
	m_ShaderManager->RenderDeferredShader(m_D3D->GetDeviceContext(),m_Model2->GetIndexCount(),shaderMatrix,&m_dsBufferClass,m_Model2->GetTexture());


	m_D3D->TurnZBufferOff();

	m_orthoWindowClass.Render(m_D3D->GetDeviceContext());
	m_ShaderManager->RenderDSLightShader(m_D3D->GetDeviceContext(),m_orthoWindowClass.GetIndexCount(),shaderMatrix,&m_dsBufferClass,m_Light);
	m_ShaderManager->RenderDSEdgeDetectAAShader(m_D3D->GetDeviceContext(),m_orthoWindowClass.GetIndexCount(),shaderMatrix,&m_dsBufferClass,m_Light);
	m_ShaderManager->RenderDSBloomShader(m_D3D->GetDeviceContext(),m_orthoWindowClass.GetIndexCount(),shaderMatrix,&m_dsBufferClass,m_Light);


	m_D3D->SetBackBufferRenderTarget();
	m_D3D->ResetViewport();
	m_D3D->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);

	m_ShaderManager->RenderDSMergeOutputShader(m_D3D->GetDeviceContext(),m_orthoWindowClass.GetIndexCount(),shaderMatrix,&m_dsBufferClass,m_Light);

	m_D3D->TurnZBufferOn();

	m_D3D->EndScene();

	return true;

}

bool CApplicationClass::RenderSceneToTexture()
{

	return true;
}