#pragma once
#include"windows.h"


interface ITestApp
{
	virtual bool InitD3D(int width, int heitht, HWND outputWindow,HINSTANCE hinstance) = 0;
	//virtual bool InitTerrain(int level,int cellSpacing)=0;

	virtual bool OnResize(int width, int height) = 0;

	virtual void OnMouseDown(int type, int x, int y) = 0;
	virtual void OnMouseMove(int type, int x, int y) = 0;

	virtual bool DrawScene() = 0;
	virtual void KeyInput(char  keycode)=0;
};


__declspec(dllexport) ITestApp* fnCreateITerrainInterface(void);
__declspec(dllexport) void fnReleaseITerrainInterface(ITestApp *piInterface);