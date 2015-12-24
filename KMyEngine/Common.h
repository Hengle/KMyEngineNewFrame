#pragma once

#include <d3dx11.h>
#include <xnamath.h>
#include <dxerr.h>
#include <cassert>  //--> �����ڳ����ʱ��ָ������
#include <algorithm>
#include <string>
#include <sstream> //--> ���ڸ�ʽת��
#include <fstream>
#include <vector>
#include "MathHelper.h"
#include "LightHelper.h"


using namespace std;

//---------------------------------------------------------------------------------------
// �򵥵�D3D ������ 
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
// ���õĺ꣺�ͷ�ɾ�� 
//---------------------------------------------------------------------------------------
#define ReleaseCOM(x) { if(x){ x->Release(); x = 0; } }
#define SafeDelete(x) {delete x,x=0;}

struct ShaderMatrix 
{
	XMFLOAT4X4 gWorld;
	XMFLOAT4X4 gView;
	XMFLOAT4X4 gProj;
};