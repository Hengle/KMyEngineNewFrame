#include "DeferredShadingMergeOutput.h"


CDeferredShadingMergeOutput::CDeferredShadingMergeOutput()
{
	m_vertexShader = 0;
	m_pixelShader = 0;

	m_layout = 0;
	m_sampleStatePoint = 0;

	//m_cbPerFramePS = 0;
	//m_cbPerObjectVS = 0;
}


CDeferredShadingMergeOutput::CDeferredShadingMergeOutput(const CDeferredShadingMergeOutput& other)
{
}


CDeferredShadingMergeOutput::~CDeferredShadingMergeOutput()
{
}


bool CDeferredShadingMergeOutput::Initialize(ID3D11Device* device, HWND hwnd)
{
	bool result;

	result = InitializeVS(device, hwnd, L"../KMyEngineData/fx/DeferredShading/DeferredShadingMergeOutput.fx");
	result = InitializePS(device, hwnd, L"../KMyEngineData/fx/DeferredShading/DeferredShadingMergeOutput.fx");
	if(!result)
	{
		return false;
	}

	return true;
}


void CDeferredShadingMergeOutput::Shutdown()
{
	ShutdownShader();

	return;
}


bool CDeferredShadingMergeOutput::Render(ID3D11DeviceContext* deviceContext, int indexCount,ShaderMatrix shaderMatrix, DeferredBuffersClass* pdb, LightClass* light)
{
	bool result;


	result = SetShaderParametersVS();
	if(!result)
	{
		return false;
	}

	result = SetShaderParametersPS(deviceContext, shaderMatrix, pdb, light);
	if(!result)
	{
		return false;
	}


	RenderShader(deviceContext, indexCount);

	return true;
}


bool CDeferredShadingMergeOutput::InitializeVS(ID3D11Device* device, HWND hwnd, WCHAR* vsFilename)
{
	
	return true;
}

bool CDeferredShadingMergeOutput::InitializePS(ID3D11Device* device, HWND hwnd, WCHAR* psFilename)
{
	HRESULT result;
	ID3D10Blob* errorMessage;
	ID3D10Blob* pixelShaderBuffer;
	D3D11_SAMPLER_DESC samplerDesc;
	D3D11_SAMPLER_DESC LinearSampleDesc;
	D3D11_BUFFER_DESC matrixBufferDesc;

	errorMessage = 0;
	pixelShaderBuffer = 0;

	result = D3DX11CompileFromFile(psFilename, NULL, NULL, "psMergeOutput", "ps_5_0", D3D10_SHADER_ENABLE_STRICTNESS, 0, NULL, 
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
		
	LinearSampleDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	LinearSampleDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	LinearSampleDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	LinearSampleDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	LinearSampleDesc.MipLODBias = 0.0f;
	LinearSampleDesc.MaxAnisotropy = 1;
	LinearSampleDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
	LinearSampleDesc.BorderColor[0] = 0;
	LinearSampleDesc.BorderColor[1] = 0;
	LinearSampleDesc.BorderColor[2] = 0;
	LinearSampleDesc.BorderColor[3] = 0;
	LinearSampleDesc.MinLOD = 0;
	LinearSampleDesc.MaxLOD = D3D11_FLOAT32_MAX;
	HR(device->CreateSamplerState(&samplerDesc, &m_sampleStateLinear));


	return true;
}

void CDeferredShadingMergeOutput::ShutdownShader()
{
	ReleaseCOM(m_vertexShader);
	ReleaseCOM(m_pixelShader);
	ReleaseCOM(m_layout);
	ReleaseCOM(m_sampleStatePoint);
	//ReleaseCOM(m_cbPerFramePS);
	//ReleaseCOM(m_cbPerObjectVS);

	return;
}


void CDeferredShadingMergeOutput::OutputShaderErrorMessage(ID3D10Blob* errorMessage, HWND hwnd, WCHAR* shaderFilename)
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

bool CDeferredShadingMergeOutput::SetShaderParametersVS()
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


bool CDeferredShadingMergeOutput::SetShaderParametersPS(ID3D11DeviceContext* deviceContext,ShaderMatrix shaderMatrix, DeferredBuffersClass* pdb, LightClass* light)
{
	HRESULT result;
	D3D11_MAPPED_SUBRESOURCE mappedResource;

	ID3D11ShaderResourceView* gVBloom = pdb->GetBloomShaderResourceView(0);
	ID3D11ShaderResourceView* gHBloom = pdb->GetBloomShaderResourceView(1);
	ID3D11ShaderResourceView* gFinalColorAA = pdb->GetEdgeDetectAASRV();

	deviceContext->PSSetShaderResources(0, 1, &gVBloom);
	deviceContext->PSSetShaderResources(1, 1, &gHBloom);
	deviceContext->PSSetShaderResources(2, 1, &gFinalColorAA);

	deviceContext->PSSetSamplers(0, 1, &m_sampleStatePoint);
	deviceContext->PSSetSamplers(1,	1, &m_sampleStateLinear);

	deviceContext->PSSetShader(m_pixelShader, NULL, 0);

	return true;
}


void CDeferredShadingMergeOutput::RenderShader(ID3D11DeviceContext* deviceContext, int indexCount)
{
	deviceContext->DrawIndexed(indexCount, 0, 0);


	return;
}