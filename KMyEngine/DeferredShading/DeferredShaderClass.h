////////////////////////////////////////////////////////////////////////////////
// Filename: deferredshaderclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _DEFERREDSHADERCLASS_H_
#define _DEFERREDSHADERCLASS_H_

#include "../Common.h"
#include "DeferredBuffersClass.h"


////////////////////////////////////////////////////////////////////////////////
// Class name: DeferredShaderClass
////////////////////////////////////////////////////////////////////////////////
class DeferredShaderClass
{
private:
	struct MatrixBufferType
	{
		XMMATRIX gWorldViewProj;
		XMMATRIX gWorldView;
	};

public:
	DeferredShaderClass();
	DeferredShaderClass(const DeferredShaderClass&);
	~DeferredShaderClass();

	bool Initialize(ID3D11Device*, HWND);
	void Shutdown();
	bool Render(ID3D11DeviceContext* deviceContext, int indexCount,ShaderMatrix shaderMatrixs, DeferredBuffersClass* pdb, ID3D11ShaderResourceView* texture);

private:
	bool InitializeShader(ID3D11Device*, HWND, WCHAR*, WCHAR*);
	void ShutdownShader();
	void OutputShaderErrorMessage(ID3D10Blob*, HWND, WCHAR*);

	bool SetShaderParameters(ID3D11DeviceContext* deviceContext, ShaderMatrix shaderMatrixs, ID3D11ShaderResourceView* texture);
	void RenderShader(ID3D11DeviceContext* deviceContext, int indexCount,DeferredBuffersClass* pdb);

private:
	ID3D11VertexShader*		m_vertexShader;
	ID3D11PixelShader*		m_pixelShader;

	ID3D11InputLayout*		m_layout;
	ID3D11SamplerState*		m_sampleStateWrap;
	ID3D11Buffer*			m_matrixBuffer;
};

#endif