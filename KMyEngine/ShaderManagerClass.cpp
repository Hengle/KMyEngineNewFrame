////////////////////////////////////////////////////////////////////////////////
// Filename: shadermanagerclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "shadermanagerclass.h"


ShaderManagerClass::ShaderManagerClass()
{
	m_TextureShader = 0;
	m_LightShader = 0;
	m_BumpMapShader = 0;

	m_dsLight = 0;
	m_deferredShading = 0;
}


ShaderManagerClass::ShaderManagerClass(const ShaderManagerClass& other)
{
}


ShaderManagerClass::~ShaderManagerClass()
{
}


bool ShaderManagerClass::Initialize(ID3D11Device* device, HWND hwnd)
{
	bool result;


	m_TextureShader = new TextureShaderClass;
	if(!m_TextureShader)
	{
		return false;
	}

	result = m_TextureShader->Initialize(device, hwnd);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the texture shader object.", L"Error", MB_OK);
		return false;
	}

	m_LightShader = new LightShaderClass;
	if(!m_LightShader)
	{
		return false;
	}

	result = m_LightShader->Initialize(device, hwnd);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the light shader object.", L"Error", MB_OK);
		return false;
	}

	m_BumpMapShader = new BumpMapShaderClass;
	if(!m_BumpMapShader)
	{
		return false;
	}

	result = m_BumpMapShader->Initialize(device, hwnd);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the bump map shader object.", L"Error", MB_OK);
		return false;
	}

	m_deferredShading = new DeferredShaderClass;
	if (!m_deferredShading)
	{
		return false;
	}
	result = m_deferredShading->Initialize(device,hwnd);
	if (!result)
	{
		return false;
	}

	m_dsLight = new CDeferredShadingLightShaderClass;
	if (!m_dsLight)
	{
		return false;
	}
	result = m_dsLight->Initialize(device,hwnd);
	if (!result)
	{
		return false;
	}

	m_dsEdgeDetectedShader = new DeferredShadingEdgeDetectAAClass;
	if (!m_dsEdgeDetectedShader)
	{
		return false;
	}
	result = m_dsEdgeDetectedShader->Initialize(device,hwnd);
	if (!result)
	{
		return false;
	}

	m_dsBloomShader = new CDeferredShadingBloomClass;
	if (!m_dsBloomShader)
	{
		return false;
	}
	result = m_dsBloomShader->Initialize(device,hwnd);
	if (!result)
	{
		return false;
	}
	
	m_dsMergeOutputShader = new CDeferredShadingMergeOutput;
	if (!m_dsMergeOutputShader)
	{
		return false;
	}
	result = m_dsMergeOutputShader->Initialize(device,hwnd);
	if (!result)
	{
		return false;
	}

	m_dsEditorTestShader = new CDeferredShadingMergeOutputEditorTest;
	if (!m_dsEditorTestShader)
	{
		return false;
	}
	result = m_dsEditorTestShader->Initialize(device,hwnd);
	if (!result)
	{
		return false;
	}

	return true;
}


void ShaderManagerClass::Shutdown()
{
	if(m_BumpMapShader)
	{
		m_BumpMapShader->Shutdown();
		delete m_BumpMapShader;
		m_BumpMapShader = 0;
	}

	if(m_LightShader)
	{
		m_LightShader->Shutdown();
		delete m_LightShader;
		m_LightShader = 0;
	}

	if(m_TextureShader)
	{
		m_TextureShader->Shutdown();
		delete m_TextureShader;
		m_TextureShader = 0;
	}

	if (m_deferredShading)
	{
		m_deferredShading->Shutdown();
		delete m_deferredShading;
		m_deferredShading= 0;
	}

	if (m_dsLight)
	{
		m_dsLight->Shutdown();
		delete m_dsLight;
		m_dsLight = 0;
	}

	if (m_dsEdgeDetectedShader)
	{
		m_dsEdgeDetectedShader->Shutdown();
		delete m_dsEdgeDetectedShader;
		m_dsEdgeDetectedShader = 0;
	}

	if (m_dsBloomShader)
	{
		m_dsBloomShader->Shutdown();
		delete m_dsBloomShader;
		m_dsBloomShader = 0;
	}
	if (m_dsMergeOutputShader)
	{
		m_dsMergeOutputShader->Shutdown();
		delete m_dsMergeOutputShader;
		m_dsMergeOutputShader = 0;
	}
	if (m_dsEditorTestShader)
	{
		m_dsEditorTestShader->Shutdown();
		delete m_dsEditorTestShader;
		m_dsEditorTestShader = 0;
	}

	return;
}


bool ShaderManagerClass::RenderTextureShader(ID3D11DeviceContext* device, int indexCount, CXMMATRIX worldMatrix, CXMMATRIX viewMatrix, CXMMATRIX projectionMatrix, 
											 ID3D11ShaderResourceView* texture)
{
	bool result;


	// Render the model using the texture shader.
	result = m_TextureShader->Render(device, indexCount, worldMatrix, viewMatrix, projectionMatrix, texture);
	if(!result)
	{
		return false;
	}

	return true;
}


bool ShaderManagerClass::RenderLightShader(ID3D11DeviceContext* deviceContext, int indexCount, CXMMATRIX worldMatrix, CXMMATRIX viewMatrix, CXMMATRIX projectionMatrix, 
										   ID3D11ShaderResourceView* texture, XMFLOAT3 lightDirection, XMFLOAT4 ambient, XMFLOAT4 diffuse, 
										   XMFLOAT3 cameraPosition, XMFLOAT4 specular, float specularPower)
{
	bool result;


	// Render the model using the light shader.
	result = m_LightShader->Render(deviceContext, indexCount, worldMatrix, viewMatrix, projectionMatrix, texture, lightDirection, ambient, diffuse, cameraPosition, 
		specular, specularPower);
	if(!result)
	{
		return false;
	}

	return true;
}


bool ShaderManagerClass::RenderBumpMapShader(ID3D11DeviceContext* deviceContext, int indexCount, CXMMATRIX worldMatrix, CXMMATRIX viewMatrix, CXMMATRIX projectionMatrix, 
											 ID3D11ShaderResourceView* colorTexture, ID3D11ShaderResourceView* normalTexture, XMFLOAT3 lightDirection, 
											 XMFLOAT4 diffuse)
{
	bool result;


	result = m_BumpMapShader->Render(deviceContext, indexCount, worldMatrix, viewMatrix, projectionMatrix, colorTexture, normalTexture, lightDirection, diffuse);
	if(!result)
	{
		return false;
	}

	return true;
}

bool ShaderManagerClass::RenderDeferredShader(ID3D11DeviceContext* deviceContext, int indexCount,ShaderMatrix shaderMatrixs, DeferredBuffersClass* pdb, ID3D11ShaderResourceView* texture,Material gMaterial)
{
	bool result;


	result = m_deferredShading->Render(deviceContext, indexCount, shaderMatrixs, pdb, texture,gMaterial);
	if(!result)
	{
		return false;
	}

	return true;
}
bool ShaderManagerClass::RenderDSLightShader(ID3D11DeviceContext* deviceContext,int indexCount, ShaderMatrix shaderMatrix, DeferredBuffersClass* pdb, LightClass* light)
{
	bool result;


	result = m_dsLight->Render(deviceContext, indexCount, shaderMatrix, pdb, light);
	if(!result)
	{
		return false;
	}

	return true;

}

bool ShaderManagerClass::RenderDSEdgeDetectAAShader(ID3D11DeviceContext* deviceContext,int indexCount, ShaderMatrix shaderMatrix, DeferredBuffersClass* pdb, LightClass* light)
{
	bool result;


	result = m_dsEdgeDetectedShader->Render(deviceContext, indexCount, shaderMatrix, pdb, light);
	if(!result)
	{
		return false;
	}

	return true;
}

bool ShaderManagerClass::RenderDSBloomShader(ID3D11DeviceContext* deviceContext,int indexCount, ShaderMatrix shaderMatrix, DeferredBuffersClass* pdb, LightClass* light)
{
	bool result;


	result = m_dsBloomShader->Render(deviceContext, indexCount, shaderMatrix, pdb, light);
	if(!result)
	{
		return false;
	}

	return true;
}

bool ShaderManagerClass::RenderDSMergeOutputShader(ID3D11DeviceContext* deviceContext,int indexCount, ShaderMatrix shaderMatrix, DeferredBuffersClass* pdb, LightClass* light)
{
	bool result;


	result = m_dsMergeOutputShader->Render(deviceContext, indexCount, shaderMatrix, pdb, light);
	if(!result)
	{
		return false;
	}

	return true;
}

bool ShaderManagerClass::RenderDSEditorTest(ID3D11DeviceContext* deviceContext,int indexCount,DeferredBuffersClass* pdb,int Option)
{
	bool result;


	result = m_dsEditorTestShader->Render(deviceContext, indexCount, pdb, Option);
	if(!result)
	{
		return false;
	}

	return true;
}