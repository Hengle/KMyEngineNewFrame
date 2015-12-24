#include "DeferredShadingBloom.h"


CDeferredShadingBloomClass::CDeferredShadingBloomClass()
{
	m_vertexShader = 0;
	m_pixelShader = 0;

	m_layout = 0;
	m_sampleStatePoint = 0;

	m_cbPerFramePS = 0;
	m_cbPerObjectVS = 0;
}


CDeferredShadingBloomClass::CDeferredShadingBloomClass(const CDeferredShadingBloomClass& other)
{
}


CDeferredShadingBloomClass::~CDeferredShadingBloomClass()
{
}


bool CDeferredShadingBloomClass::Initialize(ID3D11Device* device, HWND hwnd)
{
	bool result;

	result = InitializeVS(device, hwnd, L"../KMyEngineData/fx/DeferredShading/DeferredShadingBloom.fx");
	result = InitializePS(device, hwnd, L"../KMyEngineData/fx/DeferredShading/DeferredShadingBloom.fx");
	if(!result)
	{
		return false;
	}

	return true;
}


void CDeferredShadingBloomClass::Shutdown()
{
	ShutdownShader();

	return;
}


bool CDeferredShadingBloomClass::Render(ID3D11DeviceContext* deviceContext, int indexCount,ShaderMatrix shaderMatrix, DeferredBuffersClass* pdb, LightClass* light)
{
	bool result;

	pdb->SetBloomRenderTargets(deviceContext);

	//result = SetShaderParametersVS();
	//if(!result)
	//{
	//	return false;
	//}

	result = SetShaderParametersPS(deviceContext, shaderMatrix, pdb, light);
	if(!result)
	{
		return false;
	}


	RenderShader(deviceContext, indexCount,pdb);

	return true;
}


bool CDeferredShadingBloomClass::InitializeVS(ID3D11Device* device, HWND hwnd, WCHAR* vsFilename)
{
	
	return true;
}

bool CDeferredShadingBloomClass::InitializePS(ID3D11Device* device, HWND hwnd,WCHAR* psFilename)
{
	HRESULT result;
	ID3D10Blob* errorMessage;
	ID3D10Blob* pixelShaderBuffer;
	D3D11_SAMPLER_DESC samplerDesc;
	D3D11_BUFFER_DESC matrixBufferDesc;

	errorMessage = 0;
	pixelShaderBuffer = 0;

	result = D3DX11CompileFromFile(psFilename, NULL, NULL, "psBloom", "ps_5_0", D3D10_SHADER_ENABLE_STRICTNESS, 0, NULL, 
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

	result = device->CreatePixelShader(pixelShaderBuffer->GetBufferPointer(), pixelShaderBuffer->GetBufferSize(), NULL, &m_pixelShader);
	if(FAILED(result))
	{
		return false;
	}	

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
	HR(device->CreateBuffer(&matrixBufferDesc,NULL,&m_cbPerFramePS));

	return true;
}

void CDeferredShadingBloomClass::ShutdownShader()
{
	ReleaseCOM(m_vertexShader);
	ReleaseCOM(m_pixelShader);
	ReleaseCOM(m_layout);
	ReleaseCOM(m_sampleStatePoint);
	ReleaseCOM(m_cbPerFramePS);
	ReleaseCOM(m_cbPerObjectVS);

	return;
}


void CDeferredShadingBloomClass::OutputShaderErrorMessage(ID3D10Blob* errorMessage, HWND hwnd, WCHAR* shaderFilename)
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

bool CDeferredShadingBloomClass::SetShaderParametersVS()
{
	//HRESULT result;
	//D3D11_MAPPED_SUBRESOURCE mappedResource;
	//SCB_PEROBJECT_VS* dataPtr;

	//XMMATRIX wvp = worldMatrix * viewMatrix * projectionMatrix;

	//HR(deviceContext->Map(m_cbPerObjectVS, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource));
	//dataPtr = (SCB_PEROBJECT_VS*)mappedResource.pData;
	//dataPtr->gWorldViewProj = XMMatrixTranspose(wvp);
	//deviceContext->Unmap(m_cbPerObjectVS, 0);

	//deviceContext->VSSetConstantBuffers(0, 1, &m_cbPerObjectVS);

	//deviceContext->VSSetShader(m_vertexShader, NULL, 0);


	return true;
}


bool CDeferredShadingBloomClass::SetShaderParametersPS(ID3D11DeviceContext* deviceContext, ShaderMatrix shaderMatrix, DeferredBuffersClass* pdb, LightClass* light)
{
	HRESULT result;
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	SCB_PERFRAME_PS* dataPtr;

	int backBufferWidth = pdb->GetTextureWidth();
	int backBufferHeight = pdb->GetTextureHeight();

	ID3D11ShaderResourceView* gFinalColor = pdb->GetLightingSRV();

	HR(deviceContext->Map(m_cbPerFramePS, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource));
	dataPtr = (SCB_PERFRAME_PS*)mappedResource.pData;

	dataPtr->gPixelSize = XMFLOAT2(1.0/backBufferWidth, 1.0/backBufferHeight);

	deviceContext->Unmap(m_cbPerFramePS, 0);
	deviceContext->PSSetConstantBuffers(0, 1, &m_cbPerFramePS);

	deviceContext->PSSetShaderResources(0, 1, &gFinalColor);
	//deviceContext->PSSetShaderResources(1, 1, &gNormal);
	//deviceContext->PSSetShaderResources(2, 1, &specularTexture);
	//deviceContext->PSSetShaderResources(3, 1, &depthTexture);

	deviceContext->PSSetSamplers(0, 1, &m_sampleStatePoint);	

	deviceContext->PSSetShader(m_pixelShader, NULL, 0);

	return true;
}


void CDeferredShadingBloomClass::RenderShader(ID3D11DeviceContext* deviceContext, int indexCount,DeferredBuffersClass* pdb)
{
	
	deviceContext->DrawIndexed(indexCount, 0, 0);

	return;
}