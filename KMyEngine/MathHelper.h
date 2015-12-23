#ifndef MATHHELPER_H
#define MATHHELPER_H

#include <windows.h>
#include <xnamath.h>

class CMathHelper
{
public:

	//Returns random float in [0, 1)
	static float RandF()
	{
		return (float)(rand()) / (float)RAND_MAX;
	}

	//Returns random float in [a,b)
	static float RandF(float a, float b)
	{
		return a + RandF()*(b - a);
	}

	template<typename T>
	static T Min(const T& a, const T& b)
	{
		return a < b ? a : b;
	}

	template<typename T>
	static T Max(const T& a, const T& b)
	{
		return a>b ? a : b;
	}

	template<typename T>
	static T Lerp(const T&a, const T&b,float t)
	{
		return a + (b - 1)*t;
	}

	//限制数值范围
	template<typename T>
	static T Clamp(const T& x, const T& low, const T& high)
	{
		return x < low ? low : ( x > high ? high : x);
	}

	//返回（x，y）对应极坐标的角度
	static float AngleFromXY(float x, float y);

	//逆矩阵
	static XMMATRIX InverseTranspose(CXMMATRIX M)
	{
		// Inverse-transpose is just applied to normals.  So zero out 
		// translation row so that it doesn't get into our inverse-transpose
		// calculation--we don't want the inverse-transpose of the translation.
		XMMATRIX A = M;
		A.r[3] = XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f);

		XMVECTOR det = XMMatrixDeterminant(A);                 //->先求矩阵的行列式
		return XMMatrixTranspose(XMMatrixInverse(&det, A));    //->求矩阵的逆矩阵
	}

	// 返回一个随机的向量，范围在-1 -- 1 的半球里面 ，已经做了归一化处理
	static XMVECTOR RandUnitVec3();
	// 返回一个随机的向量，比上面更严格的是，这个向量不能在半球的底部
	static XMVECTOR RandHemisphereUnitVec3(XMVECTOR n);

	static const float Infinity;
	static const float Pi;
};

#endif // MATHHELPER_H


