////////////////////////////////////////////////////////////////////////////////
// Filename: lightshaderclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _DEFERREDSHADING_LIGHTSHADERCLASS_H_
#define _DEFERREDSHADING_LIGHTSHADERCLASS_H_

#include "../Common.h"
#include "DeferredBuffersClass.h"
#include "../LightClass.h"

class CDeferredShadingLightShaderClass
{
private:
	struct SCB_PERFRAME_PS
	{
		XMFLOAT3 gLightDirV;
		XMFLOAT3 gDiffuseLight;
		XMFLOAT3 gSpecularLight;

		XMMATRIX gProjMatrix;
	};

	struct SCB_PEROBJECT_VS
	{
		XMMATRIX gWorldViewProj;
	};

public:
	CDeferredShadingLightShaderClass();
	CDeferredShadingLightShaderClass(const CDeferredShadingLightShaderClass&);
	~CDeferredShadingLightShaderClass();

	bool Initialize(ID3D11Device*, HWND);
	void Shutdown();
	bool Render(ID3D11DeviceContext* deviceContext, int indexCount,ShaderMatrix shaderMatrix, DeferredBuffersClass* pdb, LightClass* light);

private:
	bool InitializeShader(ID3D11Device* device, HWND hwnd, WCHAR* vsFilename, WCHAR* psFilename);
	void ShutdownShader();
	void OutputShaderErrorMessage(ID3D10Blob*, HWND, WCHAR*);

	bool SetShaderParametersPS(ID3D11DeviceContext* deviceContext, ShaderMatrix shaderMatrix, DeferredBuffersClass* pdb, LightClass* light);
	bool SetShaderParametersVS(ID3D11DeviceContext* deviceContext, ShaderMatrix shaderMatrix);
	void RenderShader(ID3D11DeviceContext* deviceContext, int indexCount, DeferredBuffersClass* pdb);

private:

	ID3D11VertexShader*		m_vertexShader;
	ID3D11PixelShader*		m_pixelShader;

	ID3D11InputLayout*		m_layout;
	ID3D11SamplerState*		m_sampleStatePoint;

	ID3D11Buffer* m_cbPerFramePS;
	ID3D11Buffer* m_cbPerObjectVS;
};

#endif