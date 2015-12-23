////////////////////////////////////////////////////////////////////////////////
// Filename: lightshaderclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _DEFERREDSHADING_LIGHTSHADERCLASS_H_
#define _DEFERREDSHADING_LIGHTSHADERCLASS_H_

#include "../Common.h"

class CDeferredShadingLightShaderClass
{
private:
	struct MatrixBufferType
	{
		XMMATRIX wvp;
	};

	struct LightBufferType
	{
		XMFLOAT3 lightDirection;
		float padding;
	};

public:
	CDeferredShadingLightShaderClass();
	CDeferredShadingLightShaderClass(const CDeferredShadingLightShaderClass&);
	~CDeferredShadingLightShaderClass();

	bool Initialize(ID3D11Device*, HWND);
	void Shutdown();
	bool Render(ID3D11DeviceContext* deviceContext, int indexCount, CXMMATRIX worldMatrix, CXMMATRIX viewMatrix,
		CXMMATRIX projectionMatrix, ID3D11ShaderResourceView* colorTexture, ID3D11ShaderResourceView* normalTexture,
		CXMVECTOR lightDirection);

private:
	bool InitializeShader(ID3D11Device*, HWND, WCHAR*, WCHAR*);
	void ShutdownShader();
	void OutputShaderErrorMessage(ID3D10Blob*, HWND, WCHAR*);

	bool SetShaderParameters(ID3D11DeviceContext*, CXMMATRIX, CXMMATRIX, CXMMATRIX, ID3D11ShaderResourceView*, ID3D11ShaderResourceView*, CXMVECTOR);
	void RenderShader(ID3D11DeviceContext*, int);

private:
	ID3D11VertexShader*		m_vertexShader;
	ID3D11PixelShader*		m_pixelShader;

	ID3D11InputLayout*		m_layout;
	ID3D11SamplerState*		m_sampleState;

	ID3D11Buffer* m_matrixBuffer;
	ID3D11Buffer* m_lightBuffer;
};

#endif