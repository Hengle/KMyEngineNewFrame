////////////////////////////////////////////////////////////////////////////////
// Filename: deferredbuffersclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _DEFERREDBUFFERSCLASS_H_
#define _DEFERREDBUFFERSCLASS_H_

const int BUFFER_COUNT = 4;

#include "../Common.h"

class DeferredBuffersClass
{
public:
	DeferredBuffersClass();
	DeferredBuffersClass(const DeferredBuffersClass&);
	~DeferredBuffersClass();

	bool Initialize(ID3D11Device*, int, int);
	void Shutdown();

	bool OnResize(ID3D11Device* pd,int width,int height);

	//
	// 第一阶段：RenderGBuffer
	//
	ID3D11Texture2D* m_renderTargetTextureArray[BUFFER_COUNT];    //-->Color\Normal\Specular\Depth
	ID3D11RenderTargetView* m_renderTargetViewArray[BUFFER_COUNT];
	ID3D11ShaderResourceView* m_shaderResourceViewArray[BUFFER_COUNT];

	void SetRenderTargets(ID3D11DeviceContext*);
	void ClearRenderTargets(ID3D11DeviceContext*, float, float, float, float);

	ID3D11ShaderResourceView* GetShaderResourceView(int);

	//
	// 第二阶段：RenderLight
	//
	ID3D11Texture2D* m_FinalColorTexture;
	ID3D11RenderTargetView* m_FinalColorRTV;
	ID3D11ShaderResourceView* m_FinalColorSRV;

	void SetLightingRenderTarget(ID3D11DeviceContext* pdc);
	void ClearLightingRenderTargets(ID3D11DeviceContext* pdc,float r,float g, float b, float a);
	ID3D11ShaderResourceView* GetLightingSRV();

	//
	// 第三阶段：Edge_Detect_AA 
	//
	ID3D11Texture2D* m_FinalColorTextureAA;
	ID3D11RenderTargetView* m_FinalColorAARTV;
	ID3D11ShaderResourceView* m_FinalColorAASRV;

	void SetEdgeDetectAARenderTarget(ID3D11DeviceContext* pdc);
	void ClearEdgeDetectAARenderTargets(ID3D11DeviceContext* pdc,float r,float g, float b, float a);
	ID3D11ShaderResourceView* GetEdgeDetectAASRV();

	//
	// 第四阶段：Bloom
	//
	ID3D11Texture2D* m_BloomTextureArray[2];
	ID3D11RenderTargetView* m_BloomRTVArray[2];
	ID3D11ShaderResourceView* m_BloomSRVArray[2];

	void SetBloomRenderTargets(ID3D11DeviceContext*);
	void ClearBloomRenderTargets(ID3D11DeviceContext*, float, float, float, float);

	ID3D11ShaderResourceView* GetBloomShaderResourceView(int);

	int GetTextureWidth();
	int GetTextureHeight();

	ID3D11Texture2D* m_depthStencilBuffer;
	ID3D11DepthStencilView* m_depthStencilView;
	D3D11_VIEWPORT m_viewport;


private:
	int m_textureWidth;
	int m_textureHeight;
};

#endif