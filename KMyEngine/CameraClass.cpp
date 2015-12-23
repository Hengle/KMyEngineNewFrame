#include "CameraClass.h"

CCameraClass::CCameraClass()
{
	Init();
}

CCameraClass::~CCameraClass()
{
	Uninit();
}

void CCameraClass::Uninit()
{

}

void CCameraClass::Init()
{
	mPosition = XMFLOAT3(0.0f,0.0f,0.0f);
	mRight = XMFLOAT3(1.0f, 0.0f, 0.0f);
	mUp= XMFLOAT3(0.0f, 1.0f, 0.0f);
	mLook = XMFLOAT3 (0.0f, 0.0f, 1.0f);

	SetLens(0.25f*CMathHelper::Pi, 1.0f, 1.0f, 1000.0f);
}

XMVECTOR CCameraClass::GetPositionXM()const
{
	return XMLoadFloat3(&mPosition);
}

XMFLOAT3 CCameraClass::GetPosition()const
{
	return mPosition;
}

void CCameraClass::SetPosition(float x, float y, float z)
{
	mPosition = XMFLOAT3(x, y, z);
}

void CCameraClass::SetPosition(const XMFLOAT3& v)
{
	mPosition = v;
}

XMVECTOR CCameraClass::GetRightXM()const
{
	return XMLoadFloat3(&mRight);
}

XMFLOAT3 CCameraClass::GetRight()const
{
	return mRight;
}

XMVECTOR CCameraClass::GetUpXM()const
{
	return XMLoadFloat3(&mUp);
}

XMFLOAT3 CCameraClass::GetUp()const
{
	return mUp;
}

XMVECTOR CCameraClass::GetLookXM()const
{
	return XMLoadFloat3(&mLook);
}

XMFLOAT3 CCameraClass::GetLook()const
{
	return mLook;
}

float CCameraClass::GetNearZ()const
{
	return mNearZ;
}

float CCameraClass::GetFarZ()const
{
	return mFarZ;
}

float CCameraClass::GetAspect()const
{
	return mAspect;
}

float CCameraClass::GetFovY()const
{
	return mFovY;
}

float CCameraClass::GetFovX()const
{
	float halfWidth = 0.5f*GetNearWindowWidth();
	return 2.0f*atan(halfWidth / mNearZ);
}

float CCameraClass::GetNearWindowWidth()const
{
	return mAspect * mNearWindowHeight;
}

float CCameraClass::GetNearWindowHeight()const
{
	return mNearWindowHeight;
}

float CCameraClass::GetFarWindowWidth()const
{
	return mAspect * mFarWindowHeight;
}

float CCameraClass::GetFarWindowHeight()const
{
	return mFarWindowHeight;
}

void CCameraClass::SetLens(float fovY, float aspect, float zn, float zf)
{
	// cache properties
	mFovY = fovY;
	mAspect = aspect;
	mNearZ = zn;
	mFarZ = zf;

	mNearWindowHeight = 2.0f * mNearZ * tanf( 0.5f*mFovY );
	mFarWindowHeight  = 2.0f * mFarZ * tanf( 0.5f*mFovY );

	XMMATRIX P = XMMatrixPerspectiveFovLH(mFovY, mAspect, mNearZ, mFarZ);
	XMStoreFloat4x4(&mProj, P);
}

void CCameraClass::LookAt(FXMVECTOR pos, FXMVECTOR target, FXMVECTOR worldUp)
{
	XMVECTOR L = XMVector3Normalize(XMVectorSubtract(target, pos));
	XMVECTOR R = XMVector3Normalize(XMVector3Cross(worldUp, L));
	XMVECTOR U = XMVector3Cross(L, R);

	XMStoreFloat3(&mPosition, pos);
	XMStoreFloat3(&mLook, L);
	XMStoreFloat3(&mRight, R);
	XMStoreFloat3(&mUp, U);
}

void CCameraClass::LookAt(const XMFLOAT3& pos, const XMFLOAT3& target, const XMFLOAT3& up)
{
	/*XMVECTOR P = XMLoadFloat3(&pos);
	XMVECTOR T = XMLoadFloat3(&target);
	XMVECTOR U = XMLoadFloat3(&up);*/

	//LookAt(P, T, U);

}

XMMATRIX CCameraClass::View()const
{
	return XMLoadFloat4x4(&mView);
}

XMMATRIX CCameraClass::Proj()const
{
	return XMLoadFloat4x4(&mProj);
}

XMMATRIX CCameraClass::ViewProj()const
{
	return XMMatrixMultiply(View(), Proj());
}

void CCameraClass::Strafe(float d)
{
	// mPosition += d*mRight
	XMVECTOR s = XMVectorReplicate(d);
	XMVECTOR r = XMLoadFloat3(&mRight);
	XMVECTOR p = XMLoadFloat3(&mPosition);
	XMStoreFloat3(&mPosition, XMVectorMultiplyAdd(s, r, p));  
	//XMVectorMultiplyAdd：分量相乘后相加！-->就是在某一方向上移动多少！
	/*
	Result.x = V1.x * V2.x + V3.x;
	Result.y = V1.y * V2.y+ V3.y;
	Result.z = V1.z * V2.z+ V3.z;
	Result.w = V1.w * V2.w+ V3.w;
	*/
}

void CCameraClass::Walk(float d)
{
	// mPosition += d*mLook
	XMVECTOR s = XMVectorReplicate(d);
	XMVECTOR l = XMLoadFloat3(&mLook);
	XMVECTOR p = XMLoadFloat3(&mPosition);
	XMStoreFloat3(&mPosition, XMVectorMultiplyAdd(s, l, p));
	// 与上面同理
}

void CCameraClass::Pitch(float angle)
{
	//
	XMMATRIX R = XMMatrixRotationAxis(XMLoadFloat3(&mRight), angle);

	XMStoreFloat3(&mUp,   XMVector3TransformNormal(XMLoadFloat3(&mUp), R));
	XMStoreFloat3(&mLook, XMVector3TransformNormal(XMLoadFloat3(&mLook), R));
}

void CCameraClass::RotateY(float angle)
{

	XMMATRIX R = XMMatrixRotationY(angle);

	XMStoreFloat3(&mRight,   XMVector3TransformNormal(XMLoadFloat3(&mRight), R));
	XMStoreFloat3(&mUp, XMVector3TransformNormal(XMLoadFloat3(&mUp), R));
	XMStoreFloat3(&mLook, XMVector3TransformNormal(XMLoadFloat3(&mLook), R));
}

void CCameraClass::UpdateViewMatrix()
{
	//这里的成员函数：都已经是变化以后的了，比如说我求出了摄像机要移动的地方，和摄像机旋转变化后的三轴朝向，据此来求出要想做出这样的变换，它的变化矩阵是什么？

	XMVECTOR R = XMLoadFloat3(&mRight);
	XMVECTOR U = XMLoadFloat3(&mUp);
	XMVECTOR L = XMLoadFloat3(&mLook);
	XMVECTOR P = XMLoadFloat3(&mPosition);

	L = XMVector3Normalize(L);
	U = XMVector3Normalize(XMVector3Cross(L, R));
	R = XMVector3Cross(U, L); 

	float x = -XMVectorGetX(XMVector3Dot(P, R));
	float y = -XMVectorGetX(XMVector3Dot(P, U));
	float z = -XMVectorGetX(XMVector3Dot(P, L));

	XMStoreFloat3(&mRight, R);
	XMStoreFloat3(&mUp, U);
	XMStoreFloat3(&mLook, L);

	mView(0, 0) = mRight.x;	mView(0, 1) = mUp.x;	mView(0, 2) = mLook.x;	mView(0, 3) = 0;
	mView(1, 0) = mRight.y;	mView(1, 1) = mUp.y;	mView(1, 2) = mLook.y;	mView(1, 3) = 0;
	mView(2, 0) = mRight.z;	mView(2, 1) = mUp.z;	mView(2, 2) = mLook.z;	mView(2, 3) = 0;
	mView(3, 0) = x;		mView(3, 1) = y;		mView(3, 2) = z;		mView(3, 3) = 1;
}



//推导过程可参阅潘李亮《largeLod》文中的第5章
void Frustum::extractFromMatrix(CXMMATRIX matrix)
{
	LeftPlane.x = matrix._14 + matrix._11;
	LeftPlane.y = matrix._24 + matrix._21;
	LeftPlane.z = matrix._34 + matrix._31;
	LeftPlane.w = matrix._44 + matrix._41;

	RightPlane.x = matrix._14 - matrix._11;
	RightPlane.y = matrix._24 - matrix._21;
	RightPlane.z = matrix._34 - matrix._31;
	RightPlane.w = matrix._44 - matrix._41;

	TopPlane.x = matrix._14 - matrix._12;
	TopPlane.y = matrix._24 - matrix._22;
	TopPlane.z = matrix._34 - matrix._32;
	TopPlane.w = matrix._44 - matrix._42;

	BottomPlane.x = matrix._14 + matrix._12;
	BottomPlane.y = matrix._24 + matrix._22;
	BottomPlane.z = matrix._34 + matrix._32;
	BottomPlane.w = matrix._44 + matrix._42;

	NearPlane.x = matrix._13;
	NearPlane.y = matrix._23;
	NearPlane.z = matrix._33;
	NearPlane.w = matrix._43;

	FarPlane.x = matrix._14 - matrix._13;
	FarPlane.y = matrix._24 - matrix._23;
	FarPlane.z = matrix._34 - matrix._33;
	FarPlane.w = matrix._44 - matrix._43;

	XMStoreFloat4(&LeftPlane,XMPlaneNormalize(XMLoadFloat4(&LeftPlane)));
	XMStoreFloat4(&RightPlane,XMPlaneNormalize(XMLoadFloat4(&RightPlane)));
	XMStoreFloat4(&TopPlane ,XMPlaneNormalize(XMLoadFloat4(&TopPlane)));
	XMStoreFloat4(&BottomPlane ,XMPlaneNormalize(XMLoadFloat4(&BottomPlane)));
	XMStoreFloat4(&NearPlane ,XMPlaneNormalize(XMLoadFloat4(&NearPlane)));
	XMStoreFloat4(&FarPlane ,XMPlaneNormalize(XMLoadFloat4(&FarPlane)));

}


bool Frustum::TestPoint(XMFLOAT3 point)
{
	//---------------------------------------------------------------------------------------
	// XMPlaneDotCoord 求点到平面的距离
	// P 表示平面，V表示点
	//---------------------------------------------------------------------------------------

	if ((GetDistance(LeftPlane, point) < 0.0f)
		|| (GetDistance(RightPlane, point) < 0.0f)
		|| (GetDistance(TopPlane, point) < 0.0f)
		|| (GetDistance(BottomPlane,point) < 0.0f)
		|| (GetDistance(NearPlane,point) < 0.0f)
		|| (GetDistance(FarPlane,point) < 0.0f))
	{
		return false;
	}

	return true;
}
bool Frustum::TestSphere(XMFLOAT3 Pos, float r)
{

	if ((GetDistance(LeftPlane,Pos) + r < 0.0f)
		|| (GetDistance(RightPlane,Pos) + r < 0.0f)
		|| (GetDistance(NearPlane,Pos) + r < 0.0f)
		|| (GetDistance(FarPlane,Pos) + r < 0.0f)
		|| (GetDistance(TopPlane,Pos) + r < 0.0f)
		|| (GetDistance(BottomPlane,Pos) + r < 0.0f)
		)
	{
		return false;
	}

	return true;
}

float Frustum::GetDistance(XMFLOAT4 p, XMFLOAT3 v)
{
	XMFLOAT4 t;
	XMStoreFloat4(&t, XMPlaneDotCoord(XMLoadFloat4(&p), XMLoadFloat3(&v)));
	return t.x;
}
