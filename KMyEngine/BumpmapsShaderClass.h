////////////////////////////////////////////////////////////////////////////////
// Filename: bumpmapshaderclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _BUMPMAPSHADERCLASS_H_
#define _BUMPMAPSHADERCLASS_H_

#include "Common.h"


////////////////////////////////////////////////////////////////////////////////
// Class name: BumpMapShaderClass
////////////////////////////////////////////////////////////////////////////////
class BumpMapShaderClass
{
private:
	struct MatrixBufferType
	{
		XMMATRIX world;
		XMMATRIX view;
		XMMATRIX projection;
	};

	struct LightBufferType
	{
		XMFLOAT4 diffuseColor;
		XMFLOAT3 lightDirection;
		float padding;
	};

public:
	BumpMapShaderClass();
	BumpMapShaderClass(const BumpMapShaderClass&);
	~BumpMapShaderClass();

	bool Initialize(ID3D11Device*, HWND);
	void Shutdown();
	bool Render(ID3D11DeviceContext* deviceContext, int indexCount, CXMMATRIX worldMatrix, CXMMATRIX viewMatrix, 
		CXMMATRIX projectionMatrix, ID3D11ShaderResourceView* colorTexture, ID3D11ShaderResourceView* normalMapTexture, 
		XMFLOAT3 lightDirection, XMFLOAT4 diffuseColor);

private:
	bool InitializeShader(ID3D11Device*, HWND, WCHAR*, WCHAR*);
	void ShutdownShader();
	void OutputShaderErrorMessage(ID3D10Blob*, HWND, WCHAR*);

	bool SetShaderParameters(ID3D11DeviceContext* deviceContext, CXMMATRIX worldMatrix, 
		CXMMATRIX viewMatrix, CXMMATRIX projectionMatrix, 
		ID3D11ShaderResourceView* colorTexture, ID3D11ShaderResourceView* normalMapTexture, 
		XMFLOAT3 lightDirection, XMFLOAT4 diffuseColor);
	void RenderShader(ID3D11DeviceContext*, int);

private:
	ID3D11VertexShader* m_vertexShader;
	ID3D11PixelShader* m_pixelShader;
	ID3D11InputLayout* m_layout;
	ID3D11Buffer* m_matrixBuffer;
	ID3D11SamplerState* m_sampleState;
	ID3D11Buffer* m_lightBuffer;
};

#endif