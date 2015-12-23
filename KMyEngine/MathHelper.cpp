#include "MathHelper.h"
#include <float.h>  //->float.h与limits.h一样是定义边界值的,float.h定义的是浮点数的边界值
#include <cmath>

const float CMathHelper::Infinity = FLT_MAX;
const float CMathHelper::Pi = 3.1415926535f;

float CMathHelper::AngleFromXY(float x, float y)
{
	float theta = 0.0f;

	// Quadrant(四分之一圆:象限) I or IV
	if (x >= 0.0f)
	{
		// If x = 0, then atanf(y/x) = +pi/2 if y > 0
		//                atanf(y/x) = -pi/2 if y < 0
		theta = atanf(y / x); // in [-pi/2, +pi/2]

		if (theta < 0.0f)
			theta += 2.0f*Pi; // in [0, 2*pi).
	}

	// Quadrant II or III
	else
		theta = atanf(y / x) + Pi; // in [0, 2*pi).

	return theta;
}

XMVECTOR CMathHelper::RandUnitVec3()
{
	XMVECTOR One = XMVectorSet(1.0f, 1.0f, 1.0f, 1.0f);
	XMVECTOR Zero = XMVectorZero();

	// Keep trying until we get a point on/in the hemisphere（半球）.
	while (true)
	{
		// Generate random point in the cube [-1,1]^3. 这个时候向量的范围是在一个Cube里面
		XMVECTOR v = XMVectorSet(CMathHelper::RandF(-1.0f, 1.0f), CMathHelper::RandF(-1.0f, 1.0f), CMathHelper::RandF(-1.0f, 1.0f), 0.0f);

		// Ignore points outside the unit sphere in order to get an even distribution 
		// over the unit sphere.  Otherwise points will clump more on the sphere near 
		// the corners of the cube.

		if (XMVector3Greater(XMVector3LengthSq(v), One))
			continue;

		return XMVector3Normalize(v); //->矩阵归一：使得矩阵绝对值为1
	}
}

XMVECTOR CMathHelper::RandHemisphereUnitVec3(XMVECTOR n)
{
	XMVECTOR One = XMVectorSet(1.0f, 1.0f, 1.0f, 1.0f);
	XMVECTOR Zero = XMVectorZero();

	// Keep trying until we get a point on/in the hemisphere.
	while (true)
	{
		// Generate random point in the cube [-1,1]^3.
		XMVECTOR v = XMVectorSet(CMathHelper::RandF(-1.0f, 1.0f), CMathHelper::RandF(-1.0f, 1.0f),CMathHelper::RandF(-1.0f, 1.0f), 0.0f);

		// Ignore points outside the unit sphere in order to get an even distribution 
		// over the unit sphere.  Otherwise points will clump more on the sphere near 
		// the corners of the cube.

		if (XMVector3Greater(XMVector3LengthSq(v), One))
			continue;

		// Ignore points in the bottom hemisphere.
		if (XMVector3Less(XMVector3Dot(n, v), Zero))
			continue;

		return XMVector3Normalize(v);
	}
}
