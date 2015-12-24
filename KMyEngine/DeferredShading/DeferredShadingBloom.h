////////////////////////////////////////////////////////////////////////////////
// Filename: lightshaderclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _DEFERREDSHADING_BLOOM_CLASS_H_
#define _DEFERREDSHADING_BLOOM_CLASS_H_

#include "../Common.h"
#include "../LightClass.h"
#include "DeferredBuffersClass.h"

class CDeferredShadingBloomClass
{
private:
	struct SCB_PERFRAME_PS
	{
		XMFLOAT2 gPixelSize;
		XMFLOAT2 nouse;
	};
			
public:
	CDeferredShadingBloomClass();
	CDeferredShadingBloomClass(const CDeferredShadingBloomClass&);
	~CDeferredShadingBloomClass();

	bool Initialize(ID3D11Device*, HWND);
	void Shutdown();
	bool Render(ID3D11DeviceContext* deviceContext, int indexCount,ShaderMatrix shaderMatrix, DeferredBuffersClass* pdb, LightClass* light);

private:
	bool InitializeVS(ID3D11Device* device, HWND hwnd, WCHAR* vsFilename);
	bool InitializePS(ID3D11Device* device, HWND hwnd, WCHAR* psFilename);

	void ShutdownShader();
	void OutputShaderErrorMessage(ID3D10Blob*, HWND, WCHAR*);

	bool SetShaderParametersPS(ID3D11DeviceContext* deviceContext, ShaderMatrix shaderMatrix, DeferredBuffersClass* pdb, LightClass* light);
	bool SetShaderParametersVS();
	void RenderShader(ID3D11DeviceContext* device, int indexCount,DeferredBuffersClass* db);

private:

	ID3D11VertexShader*		m_vertexShader;
	ID3D11PixelShader*		m_pixelShader;

	ID3D11InputLayout*		m_layout;
	ID3D11SamplerState*		m_sampleStatePoint;

	ID3D11Buffer* m_cbPerFramePS;
	ID3D11Buffer* m_cbPerObjectVS;
};

#endif