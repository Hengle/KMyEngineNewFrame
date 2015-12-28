////////////////////////////////////////////////////////////////////////////////
// Filename: lightshaderclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _DEFERREDSHADING_MERGEOUTPUT_EDITORTEST_CLASS_H_
#define _DEFERREDSHADING_MERGEOUTPUT_EDITORTEST_CLASS_H_

#include "../Common.h"
#include "../LightClass.h"
#include "DeferredBuffersClass.h"

class CDeferredShadingMergeOutputEditorTest
{
private:
	enum RenderOption
	{
		RO_Diffuse = 0,
		RO_Nomarl = 1,
		RO_Specular = 2,
		RO_Depth =3,
		RO_WithLight = 4,
		RO_WithEdegeDetectedAA=5,
		RO_WithBloom = 6
	};
			
public:
	CDeferredShadingMergeOutputEditorTest();
	CDeferredShadingMergeOutputEditorTest(const CDeferredShadingMergeOutputEditorTest&);
	~CDeferredShadingMergeOutputEditorTest();

	bool Initialize(ID3D11Device*, HWND);
	void Shutdown();
	bool Render(ID3D11DeviceContext* deviceContext,int indexCount,DeferredBuffersClass* pdb,int Option);

private:
	bool InitializeVS(ID3D11Device* device, HWND hwnd, WCHAR* vsFilename);
	bool InitializePS(ID3D11Device* device, HWND hwnd, WCHAR* psFilename);

	void ShutdownShader();
	void OutputShaderErrorMessage(ID3D10Blob*, HWND, WCHAR*);

	bool SetShaderParametersPS(ID3D11DeviceContext* deviceContext, DeferredBuffersClass* pdb,int Option);
	bool SetShaderParametersVS();
	void RenderShader(ID3D11DeviceContext* device, int indexCount);

private:

	ID3D11VertexShader*		m_vertexShader;
	ID3D11PixelShader*		m_pixelShader;

	ID3D11InputLayout*		m_layout;
	ID3D11SamplerState*		m_sampleStateLinear;

	//ID3D11Buffer* m_cbPerFramePS;
	//ID3D11Buffer* m_cbPerObjectVS;
};

#endif