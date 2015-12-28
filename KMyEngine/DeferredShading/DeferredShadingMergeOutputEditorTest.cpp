#include "DeferredShadingMergeOutputEditorTest.h"
#include "../ShaderManagerClass.h"

CDeferredShadingMergeOutputEditorTest::CDeferredShadingMergeOutputEditorTest()
{
	m_vertexShader = 0;
	m_pixelShader = 0;

	m_layout = 0;
	m_sampleStateLinear = 0;
	//m_cbPerFramePS = 0;
	//m_cbPerObjectVS = 0;
}


CDeferredShadingMergeOutputEditorTest::CDeferredShadingMergeOutputEditorTest(const CDeferredShadingMergeOutputEditorTest& other)
{
}


CDeferredShadingMergeOutputEditorTest::~CDeferredShadingMergeOutputEditorTest()
{
}


bool CDeferredShadingMergeOutputEditorTest::Initialize(ID3D11Device* device, HWND hwnd)
{
	bool result;

	result = InitializeVS(device, hwnd, L"../KMyEngineData/fx/DeferredShading/DeferredShadingMergeOutputEditorTest.fx");
	result = InitializePS(device, hwnd, L"../KMyEngineData/fx/DeferredShading/DeferredShadingMergeOutputEditorTest.fx");
	if(!result)
	{
		return false;
	}

	return true;
}


void CDeferredShadingMergeOutputEditorTest::Shutdown()
{
	ShutdownShader();

	return;
}


bool CDeferredShadingMergeOutputEditorTest::Render(ID3D11DeviceContext* deviceContext,int indexCount,DeferredBuffersClass* pdb,int Option)
{
	bool result;


	result = SetShaderParametersVS();
	if(!result)
	{
		return false;
	}

	result = SetShaderParametersPS(deviceContext, pdb,Option);
	if(!result)
	{
		return false;
	}


	RenderShader(deviceContext, indexCount);

	return true;
}


bool CDeferredShadingMergeOutputEditorTest::InitializeVS(ID3D11Device* device, HWND hwnd, WCHAR* vsFilename)
{
	
	return true;
}

bool CDeferredShadingMergeOutputEditorTest::InitializePS(ID3D11Device* device, HWND hwnd, WCHAR* psFilename)
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
	HR(device->CreateSamplerState(&LinearSampleDesc, &m_sampleStateLinear));


	return true;
}

void CDeferredShadingMergeOutputEditorTest::ShutdownShader()
{
	ReleaseCOM(m_vertexShader);
	ReleaseCOM(m_pixelShader);
	ReleaseCOM(m_layout);
	ReleaseCOM(m_sampleStateLinear);
	//ReleaseCOM(m_cbPerFramePS);
	//ReleaseCOM(m_cbPerObjectVS);

	return;
}


void CDeferredShadingMergeOutputEditorTest::OutputShaderErrorMessage(ID3D10Blob* errorMessage, HWND hwnd, WCHAR* shaderFilename)
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

bool CDeferredShadingMergeOutputEditorTest::SetShaderParametersVS()
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


bool CDeferredShadingMergeOutputEditorTest::SetShaderParametersPS(ID3D11DeviceContext* deviceContext, DeferredBuffersClass* pdb,int Option)
{
	HRESULT result;
	D3D11_MAPPED_SUBRESOURCE mappedResource;

	ID3D11ShaderResourceView* outputSRV = pdb->GetShaderResourceView(0);

	switch (Option)
	{
	case RO_Nomarl:
		outputSRV = pdb->GetShaderResourceView(1);
		break;
	case RO_Specular:
		outputSRV = pdb->GetShaderResourceView(2);
		break;
	case RO_Depth:
		outputSRV = pdb->GetShaderResourceView(3);
		break;
	case RO_WithLight:
		outputSRV = pdb->GetLightingSRV();
		break;
	case RO_WithEdegeDetectedAA:
		outputSRV = pdb->GetEdgeDetectAASRV();
		break;
	default:
		outputSRV = pdb->GetShaderResourceView(0);
		break;
	}

	deviceContext->PSSetShaderResources(0, 1, &outputSRV);
	deviceContext->PSSetSamplers(1,	1, &m_sampleStateLinear);

	deviceContext->PSSetShader(m_pixelShader, NULL, 0);

	return true;
}


void CDeferredShadingMergeOutputEditorTest::RenderShader(ID3D11DeviceContext* deviceContext, int indexCount)
{
	deviceContext->DrawIndexed(indexCount, 0, 0);

	ID3D11ShaderResourceView* gNull = NULL;
	deviceContext->PSSetShaderResources(0, 1, &gNull);
	
	return;
}