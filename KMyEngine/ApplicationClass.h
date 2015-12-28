////////////////////////////////////////////////////////////////////////////////
// Filename: Application.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _APPLICATION_H_
#define _APPLICATION_H_


///////////////////////
// MY CLASS INCLUDES //
///////////////////////
#include "D3Dclass.h"
#include "ShaderManagerClass.h"
#include "CameraClass.h"
#include "LightClass.h"
#include "ModelClass.h"
#include "BumpmapsModelClass.h"
#include "MyTestInterfaces.h"
#include "InputClass.h"

#include "DeferredShading/DeferredBuffersClass.h"
#include "DeferredShading/OrthoWindowClass.h"

/////////////
// GLOBALS //
/////////////
const bool FULL_SCREEN = false;
const bool VSYNC_ENABLED = true;
const float SCREEN_DEPTH = 1000.0f;
const float SCREEN_NEAR = 5.0f;


////////////////////////////////////////////////////////////////////////////////
// Class name: CApplicationClass
////////////////////////////////////////////////////////////////////////////////
class CApplicationClass : public ITestApp
{
public:
	CApplicationClass();
	CApplicationClass(const CApplicationClass&);
	~CApplicationClass();

	bool InitD3D(int width, int heitht, HWND outputWindow,HINSTANCE hinstance);
	bool DrawScene(int type);
	bool OnResize(int width, int height);
	void OnMouseDown(int type, int x, int y);
	void OnMouseMove(int type, int x, int y);
	void KeyInput(char  keycode);
	void ChangeLightDir(int type,float value);

	bool Initialize(int width, int height , HWND hwnd,HINSTANCE hinstance);
	void Shutdown();
	bool Frame();

private:
	bool Render();

	bool RenderMultiShaderTest();

	bool RenderSceneToTexture();
	bool RenderDeferredShadingTest();

	bool ChooseRenderOption(int option);

private:
	D3DClass* m_D3D;
	//InputClass* m_Input;
	ShaderManagerClass* m_ShaderManager;
	CCameraClass* m_Camera;
	LightClass* m_Light;
	ModelClass* m_Model1;
	ModelClass* m_Model2;
	BumpModelClass* m_Model3;

	DeferredBuffersClass m_dsBufferClass;
	OrthoWindowClass m_orthoWindowClass;

	bool isNotFirst;

	POINT	mLastMousePos;
};

#endif