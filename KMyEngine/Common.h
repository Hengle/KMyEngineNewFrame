#pragma once

#include <d3dx11.h>
#include <xnamath.h>
#include <dxerr.h>
#include <cassert>  //--> 可以在出错的时候指出错误
#include <algorithm>
#include <string>
#include <sstream> //--> 用于格式转换
#include <fstream>
#include <vector>
#include "MathHelper.h"
#include "LightHelper.h"


using namespace std;

//---------------------------------------------------------------------------------------
// 简单的D3D 错误检查 
//---------------------------------------------------------------------------------------
#if defined(DEBUG) | defined(_DEBUG)
#ifndef HR
#define HR(x)                                              \
	{                                                          \
	HRESULT hr = (x);                                      \
	if (FAILED(hr))                                         \
		{                                                      \
		DXTrace(__FILE__, (DWORD)__LINE__, hr, L#x, true); \
		}                                                      \
	}
#endif

#else
#ifndef HR
#define HR(x) (x)
#endif
#endif 

//---------------------------------------------------------------------------------------
// DebugNew
//---------------------------------------------------------------------------------------

#ifdef _DEBUG
#define DEBUG_CLIENTBLOCK    new( _CLIENT_BLOCK, __FILE__, __LINE__)
#else
#define DEBUG_CLIENTBLOCK
#endif
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#ifdef _DEBUG
#define new DEBUG_CLIENTBLOCK
#endif

//---------------------------------------------------------------------------------------
// 常用的宏：释放删除 
//---------------------------------------------------------------------------------------
#define ReleaseCOM(x) { if(x){ x->Release(); x = 0; } }
#define SafeDelete(x) {delete x,x=0;}

struct ShaderMatrix 
{
	XMFLOAT4X4 gWorld;
	XMFLOAT4X4 gView;
	XMFLOAT4X4 gProj;
};