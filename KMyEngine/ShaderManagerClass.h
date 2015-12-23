////////////////////////////////////////////////////////////////////////////////
// Filename: shadermanagerclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _SHADERMANAGERCLASS_H_
#define _SHADERMANAGERCLASS_H_


#include "d3dclass.h"
#include "textureshaderclass.h"
#include "lightshaderclass.h"
#include "BumpmapsShaderClass.h"

//////////////////////////////////////////////////////////////////////////
// —”≥Ÿ‰÷»æ
//////////////////////////////////////////////////////////////////////////
#include "DeferredShading/DeferredShaderClass.h"
#include "DeferredShading/DeferredShadingLightShaderClass.h"

////////////////////////////////////////////////////////////////////////////////
// Class name: ShaderManagerClass
////////////////////////////////////////////////////////////////////////////////
class ShaderManagerClass
{
public:
	ShaderManagerClass();
	ShaderManagerClass(const ShaderManagerClass&);
	~ShaderManagerClass();

	bool Initialize(ID3D11Device*, HWND);
	void Shutdown();

	bool RenderTextureShader(ID3D11DeviceContext*, int, CXMMATRIX, CXMMATRIX, CXMMATRIX, ID3D11ShaderResourceView*);

	bool RenderLightShader(ID3D11DeviceContext*, int, CXMMATRIX, CXMMATRIX, CXMMATRIX, ID3D11ShaderResourceView*, 
		XMFLOAT3, XMFLOAT4, XMFLOAT4, XMFLOAT3, XMFLOAT4, float);

	bool RenderBumpMapShader(ID3D11DeviceContext*, int, CXMMATRIX, CXMMATRIX, CXMMATRIX, ID3D11ShaderResourceView*, 
		ID3D11ShaderResourceView*, XMFLOAT3, XMFLOAT4);

	bool RenderDeferredShader(ID3D11DeviceContext* deviceContext, int indexCount, CXMMATRIX worldMatrix, CXMMATRIX viewMatrix, 
		CXMMATRIX projectionMatrix, ID3D11ShaderResourceView* texture);

	bool RenderDSLightShader(ID3D11DeviceContext* deviceContext, int indexCount, CXMMATRIX worldMatrix, CXMMATRIX viewMatrix, 
		CXMMATRIX projectionMatrix, ID3D11ShaderResourceView* colorTexture, ID3D11ShaderResourceView* normalTexture,
		CXMVECTOR lightDirection);

	DeferredShaderClass*				m_deferredShading;
	CDeferredShadingLightShaderClass*   m_dsLight;

private:
	TextureShaderClass* m_TextureShader;
	LightShaderClass* m_LightShader;
	BumpMapShaderClass* m_BumpMapShader;


};

#endif