////////////////////////////////////////////////////////////////////////////////
// Filename: deferredshaderclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _DEFERREDSHADERCLASS_H_
#define _DEFERREDSHADERCLASS_H_

#include "../Common.h"


////////////////////////////////////////////////////////////////////////////////
// Class name: DeferredShaderClass
////////////////////////////////////////////////////////////////////////////////
class DeferredShaderClass
{
private:
	struct MatrixBufferType
	{
		XMMATRIX gWorldInvTranspose;
		XMMATRIX wvp;
	};

public:
	DeferredShaderClass();
	DeferredShaderClass(const DeferredShaderClass&);
	~DeferredShaderClass();

	bool Initialize(ID3D11Device*, HWND);
	void Shutdown();
	bool Render(ID3D11DeviceContext* deviceContext, int indexCount, CXMMATRIX worldMatrix, CXMMATRIX viewMatrix, 
		CXMMATRIX projectionMatrix, ID3D11ShaderResourceView* texture);

private:
	bool InitializeShader(ID3D11Device*, HWND, WCHAR*, WCHAR*);
	void ShutdownShader();
	void OutputShaderErrorMessage(ID3D10Blob*, HWND, WCHAR*);

	bool SetShaderParameters(ID3D11DeviceContext*, CXMMATRIX, CXMMATRIX, CXMMATRIX, ID3D11ShaderResourceView*);
	void RenderShader(ID3D11DeviceContext*, int);

private:
	ID3D11VertexShader*		m_vertexShader;
	ID3D11PixelShader*		m_pixelShader;

	ID3D11InputLayout*		m_layout;
	ID3D11SamplerState*		m_sampleStateWrap;
	ID3D11Buffer*			m_matrixBuffer;
};

#endif