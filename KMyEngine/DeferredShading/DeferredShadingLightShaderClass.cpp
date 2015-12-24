////////////////////////////////////////////////////////////////////////////////
// Filename: lightshaderclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "DeferredShadingLightShaderClass.h"


CDeferredShadingLightShaderClass::CDeferredShadingLightShaderClass()
{
	m_vertexShader = 0;
	m_pixelShader = 0;

	m_layout = 0;
	m_sampleStatePoint = 0;

	m_cbPerFramePS = 0;
	m_cbPerObjectVS = 0;
}


CDeferredShadingLightShaderClass::CDeferredShadingLightShaderClass(const CDeferredShadingLightShaderClass& other)
{
}


CDeferredShadingLightShaderClass::~CDeferredShadingLightShaderClass()
{
}


bool CDeferredShadingLightShaderClass::Initialize(ID3D11Device* device, HWND hwnd)
{
	bool result;

	result = InitializeShader(device, hwnd, L"../KMyEngineData/fx/DeferredShading/DeferredShadingScreenQuad.fx", L"../KMyEngineData/fx/DeferredShading/DeferredShadingLighting.fx");
	if(!result)
	{
		return false;
	}

	return true;
}


void CDeferredShadingLightShaderClass::Shutdown()
{
	ShutdownShader();

	return;
}


bool CDeferredShadingLightShaderClass::Render(ID3D11DeviceContext* deviceContext,int indexCount, ShaderMatrix shaderMatrix, DeferredBuffersClass* pdb, LightClass* light)
{
	bool result;

	pdb->SetLightingRenderTarget(deviceContext);

	result = SetShaderParametersVS(deviceContext,shaderMatrix);
	if(!result)
	{
		return false;
	}

	result = SetShaderParametersPS(deviceContext, shaderMatrix,pdb,light);
	if(!result)
	{
		return false;
	}


	RenderShader(deviceContext, indexCount,pdb);

	return true;
}


bool CDeferredShadingLightShaderClass::InitializeShader(ID3D11Device* device, HWND hwnd, WCHAR* vsFilename, WCHAR* psFilename)
{
	HRESULT result;
	ID3D10Blob* errorMessage;
	ID3D10Blob* vertexShaderBuffer;
	ID3D10Blob* pixelShaderBuffer;
	D3D11_INPUT_ELEMENT_DESC polygonLayout[3];
	unsigned int numElements;
	D3D11_SAMPLER_DESC samplerDesc;
	D3D11_BUFFER_DESC matrixBufferDesc;

	errorMessage = 0;
	vertexShaderBuffer = 0;
	pixelShaderBuffer = 0;

	result = D3DX11CompileFromFile(vsFilename, NULL, NULL, "DeferredScreenQuadVertexShader", "vs_5_0", D3D10_SHADER_ENABLE_STRICTNESS, 0, NULL, 
		&vertexShaderBuffer, &errorMessage, NULL);

	if(FAILED(result))
	{
		if(errorMessage)
		{
			OutputShaderErrorMessage(errorMessage, hwnd, vsFilename);
		}
		else
		{
			MessageBox(hwnd, vsFilename, L"Missing Shader File", MB_OK);
		}

		return false;
	}


	result = D3DX11CompileFromFile(psFilename, NULL, NULL, "psLightStage", "ps_5_0", D3D10_SHADER_ENABLE_STRICTNESS, 0, NULL, 
								   &pixelShaderBuffer, &errorMessage, NULL);
	if(FAILED(result))
	{
		if(errorMessage)
		{
			OutputShaderErrorMessage(errorMessage, hwnd, psFilename);
		}
		else
		{
			MessageBox(hwnd, psFilename, L"Missing Shader File", MB_OK);
		}

		return false;
	}

	// Create the vertex shader from the buffer.
	result = device->CreateVertexShader(vertexShaderBuffer->GetBufferPointer(), vertexShaderBuffer->GetBufferSize(), NULL, &m_vertexShader);
	if(FAILED(result))
	{
		return false;
	}

	result = device->CreatePixelShader(pixelShaderBuffer->GetBufferPointer(), pixelShaderBuffer->GetBufferSize(), NULL, &m_pixelShader);
	if(FAILED(result))
	{
		return false;
	}

	polygonLayout[0].SemanticName = "POSITION";
	polygonLayout[0].SemanticIndex = 0;
	polygonLayout[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;
	polygonLayout[0].InputSlot = 0;
	polygonLayout[0].AlignedByteOffset = 0;
	polygonLayout[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	polygonLayout[0].InstanceDataStepRate = 0;


	polygonLayout[1].SemanticName = "TEXCOORD";
	polygonLayout[1].SemanticIndex = 0;
	polygonLayout[1].Format = DXGI_FORMAT_R32G32_FLOAT;
	polygonLayout[1].InputSlot = 0;
	polygonLayout[1].AlignedByteOffset =12 /*D3D11_APPEND_ALIGNED_ELEMENT*/;
	polygonLayout[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	polygonLayout[1].InstanceDataStepRate = 0;

	HR(device->CreateInputLayout(polygonLayout, 2, vertexShaderBuffer->GetBufferPointer(), vertexShaderBuffer->GetBufferSize(), &m_layout));

	vertexShaderBuffer->Release();
	vertexShaderBuffer = 0;

	pixelShaderBuffer->Release();
	pixelShaderBuffer = 0;

	samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
	samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.MipLODBias = 0.0f;
	samplerDesc.MaxAnisotropy = 1;
	samplerDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
	samplerDesc.BorderColor[0] = 0;
	samplerDesc.BorderColor[1] = 0;
	samplerDesc.BorderColor[2] = 0;
	samplerDesc.BorderColor[3] = 0;
	samplerDesc.MinLOD = 0;
	samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;

	HR(device->CreateSamplerState(&samplerDesc, &m_sampleStatePoint));

	matrixBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	matrixBufferDesc.ByteWidth = sizeof(SCB_PERFRAME_PS);
	matrixBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	matrixBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	matrixBufferDesc.MiscFlags = 0;
	matrixBufferDesc.StructureByteStride = 0;

	HR(device->CreateBuffer(&matrixBufferDesc, NULL, &m_cbPerFramePS));

	matrixBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	matrixBufferDesc.ByteWidth = sizeof(SCB_PEROBJECT_VS);
	matrixBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	matrixBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	matrixBufferDesc.MiscFlags = 0;
	matrixBufferDesc.StructureByteStride = 0;

	HR(device->CreateBuffer(&matrixBufferDesc, NULL, &m_cbPerObjectVS));

	return true;
}


void CDeferredShadingLightShaderClass::ShutdownShader()
{
	ReleaseCOM(m_vertexShader);
	ReleaseCOM(m_pixelShader);
	ReleaseCOM(m_layout);
	ReleaseCOM(m_sampleStatePoint);
	ReleaseCOM(m_cbPerFramePS);
	ReleaseCOM(m_cbPerObjectVS);

	return;
}


void CDeferredShadingLightShaderClass::OutputShaderErrorMessage(ID3D10Blob* errorMessage, HWND hwnd, WCHAR* shaderFilename)
{
	char* compileErrors;
	unsigned long bufferSize, i;
	ofstream fout;


	compileErrors = (char*)(errorMessage->GetBufferPointer());

	bufferSize = errorMessage->GetBufferSize();

	fout.open("shader-error.txt");

	for(i=0; i<bufferSize; i++)
	{
		fout << compileErrors[i];
	}

	fout.close();

	errorMessage->Release();
	errorMessage = 0;

	MessageBox(hwnd, L"Error compiling shader.  Check shader-error.txt for message.", shaderFilename, MB_OK);

	return;
}

bool CDeferredShadingLightShaderClass::SetShaderParametersVS(ID3D11DeviceContext* deviceContext, ShaderMatrix shaderMatrix)
{
	HRESULT result;
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	SCB_PEROBJECT_VS* dataPtr;

	XMMATRIX worldMatrix = XMLoadFloat4x4(&shaderMatrix.gWorld);
	XMMATRIX viewMatrix = XMLoadFloat4x4(&shaderMatrix.gView);
	XMMATRIX projMatrix = XMLoadFloat4x4(&shaderMatrix.gProj);

	XMMATRIX wvp = worldMatrix * viewMatrix * projMatrix;

	HR(deviceContext->Map(m_cbPerObjectVS, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource));
	dataPtr = (SCB_PEROBJECT_VS*)mappedResource.pData;
	dataPtr->gWorldViewProj = XMMatrixTranspose(wvp);
	deviceContext->Unmap(m_cbPerObjectVS, 0);

	deviceContext->IASetInputLayout(m_layout);
	deviceContext->VSSetConstantBuffers(0, 1, &m_cbPerObjectVS);

	deviceContext->VSSetShader(m_vertexShader, NULL, 0);


	return true;
}


bool CDeferredShadingLightShaderClass::SetShaderParametersPS(ID3D11DeviceContext* deviceContext, ShaderMatrix shaderMatrix, DeferredBuffersClass* pdb, LightClass* light)
{
	HRESULT result;
    D3D11_MAPPED_SUBRESOURCE mappedResource;
	SCB_PERFRAME_PS* dataPtr;

	XMFLOAT3 lightDirection = light->GetDirection();
	XMFLOAT3 gDiffuseLight = XMFLOAT3(light->GetDiffuseColor().x,light->GetDiffuseColor().y,light->GetDiffuseColor().z);
	XMFLOAT3 gSpecularLight = XMFLOAT3(light->GetSpecularColor().x,light->GetSpecularColor().y,light->GetSpecularColor().z);


	ID3D11ShaderResourceView* colorTexture = pdb->GetShaderResourceView(0);
	ID3D11ShaderResourceView* normalTexture = pdb->GetShaderResourceView(1);
	ID3D11ShaderResourceView* specularTexture = pdb->GetShaderResourceView(2);
	ID3D11ShaderResourceView* depthTexture = pdb->GetShaderResourceView(3);


	HR(deviceContext->Map(m_cbPerFramePS, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource));
	dataPtr = (SCB_PERFRAME_PS*)mappedResource.pData;

	dataPtr->gLightDirV = lightDirection;
	dataPtr->gDiffuseLight = gDiffuseLight;
	dataPtr->gSpecularLight = gSpecularLight;
	dataPtr->gProjMatrix = XMMatrixTranspose(XMLoadFloat4x4(&shaderMatrix.gProj));

	deviceContext->Unmap(m_cbPerFramePS, 0);
	deviceContext->PSSetConstantBuffers(0, 1, &m_cbPerFramePS);

	deviceContext->PSSetShaderResources(0, 1, &colorTexture);
	deviceContext->PSSetShaderResources(1, 1, &normalTexture);
	deviceContext->PSSetShaderResources(2, 1, &specularTexture);
	deviceContext->PSSetShaderResources(3, 1, &depthTexture);

	deviceContext->PSSetSamplers(0, 1, &m_sampleStatePoint);	

	deviceContext->PSSetShader(m_pixelShader, NULL, 0);

	return true;
}


void CDeferredShadingLightShaderClass::RenderShader(ID3D11DeviceContext* deviceContext, int indexCount,DeferredBuffersClass* pdb)
{
	

	deviceContext->DrawIndexed(indexCount, 0, 0);

	return;
}