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

	//������ֵ��Χ
	template<typename T>
	static T Clamp(const T& x, const T& low, const T& high)
	{
		return x < low ? low : ( x > high ? high : x);
	}

	//���أ�x��y����Ӧ������ĽǶ�
	static float AngleFromXY(float x, float y);

	//�����
	static XMMATRIX InverseTranspose(CXMMATRIX M)
	{
		// Inverse-transpose is just applied to normals.  So zero out 
		// translation row so that it doesn't get into our inverse-transpose
		// calculation--we don't want the inverse-transpose of the translation.
		XMMATRIX A = M;
		A.r[3] = XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f);

		XMVECTOR det = XMMatrixDeterminant(A);                 //->������������ʽ
		return XMMatrixTranspose(XMMatrixInverse(&det, A));    //->�����������
	}

	// ����һ���������������Χ��-1 -- 1 �İ������� ���Ѿ����˹�һ������
	static XMVECTOR RandUnitVec3();
	// ����һ���������������������ϸ���ǣ�������������ڰ���ĵײ�
	static XMVECTOR RandHemisphereUnitVec3(XMVECTOR n);

	static const float Infinity;
	static const float Pi;
};

#endif // MATHHELPER_H


