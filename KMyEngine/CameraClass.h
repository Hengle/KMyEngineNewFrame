//******************************************************************************************************************************************************************************************
// 实现了两个功能：1.视角矩阵 -> 摄像机要移动到某一点、和在当点下的三轴朝向，所需要的视角变换
//								 用到的函数：LookAt()...UpdateViewMatrix()
//				   2.投影矩阵 -> 根据投影相关参数：远近平面、视角大小、投影面长宽比求投影矩阵
//
// 其实，这架摄像机它是虚拟的，是不存在的，它唯一的任务就是去帮助我们计算物体的变化,确定物体的位置！在明白一点，就是虽然我移动的是摄像机，其实我是通过摄像机，最终目标是移动世界里面的所有物体！
//*******************************************************************************************************************************************************************************************

#ifndef CAMERA_H
#define CAMERA_H
#include "Common.h"

class CCameraClass
{
public:
	CCameraClass();
	~CCameraClass();

	void Init();	
	void Uninit();

	// 获得、设置摄像机位置、朝向相关参数
	XMVECTOR GetPositionXM()const;
	XMFLOAT3 GetPosition()const;
	void SetPosition(float x, float y, float z);
	void SetPosition(const XMFLOAT3& v);

	XMVECTOR GetRightXM()const;
	XMFLOAT3 GetRight()const;
	XMVECTOR GetUpXM()const;
	XMFLOAT3 GetUp()const;
	XMVECTOR GetLookXM()const;
	XMFLOAT3 GetLook()const;

	// 获得投影矩阵平截头体相关信息
	float GetNearZ()const;
	float GetFarZ()const;
	float GetAspect()const;
	float GetFovY()const;
	float GetFovX()const;

	// Get near and far plane dimensions in view space coordinates.
	float GetNearWindowWidth()const;
	float GetNearWindowHeight()const;
	float GetFarWindowWidth()const;
	float GetFarWindowHeight()const;

	// 获得视角 投影矩阵
	XMMATRIX View()const;
	XMMATRIX Proj()const;
	XMMATRIX ViewProj()const;
	

	// 设置投影相关参数
	void SetLens(float fovY, float aspect, float zn, float zf);

	// 通过位置+观察点来设置视角矩阵的那两个参数：位置+朝向三坐标,也就是说我可以手动设置他们
	void LookAt(FXMVECTOR pos, FXMVECTOR target, FXMVECTOR worldUp);
	void LookAt(const XMFLOAT3& pos, const XMFLOAT3& target, const XMFLOAT3& up);	

	// 基本操作
	void Strafe(float d);						 //左右平移
	virtual void Walk(float d);		             //前后行走
	virtual void Pitch(float angle);             //上下点头
	virtual void RotateY(float angle);           //左右摇头

	// After modifying camera position/orientation, call to rebuild the view matrix.
	// 当修改了摄像机位置或朝向，更新视角矩阵
	void UpdateViewMatrix();

protected:

	// Camera coordinate system with coordinates relative to world space.
	// 世界坐标系下，摄像机类的核心参数：位置、当前朝向的三个轴-->用来生成最终的视角变换矩阵
	XMFLOAT3 mPosition;
	XMFLOAT3 mRight;
	XMFLOAT3 mUp;
	XMFLOAT3 mLook;

	// Cache frustum properties.
	// 投影相关参数：远近平面、视角大小、投影面长宽比
	float mNearZ;         
	float mFarZ;
	float mAspect;
	float mFovY;
	float mNearWindowHeight;
	float mFarWindowHeight;

	// Cache View/Proj matrices.
	// 视角矩阵、投影矩阵
	XMFLOAT4X4 mView;
	XMFLOAT4X4 mProj;
};


//平截头体，用6个平面表示并且含有一个包围盒和平截头体的八个顶点
struct Frustum
{
	XMFLOAT4 LeftPlane;
	XMFLOAT4 RightPlane;
	XMFLOAT4 TopPlane;
	XMFLOAT4 BottomPlane;
	XMFLOAT4 NearPlane;
	XMFLOAT4 FarPlane;

	//提取平截头体6个平面
	void extractFromMatrix(CXMMATRIX& matrix);

	bool TestPoint(const XMFLOAT3 point);
	bool TestSphere(const XMFLOAT3 Pos, float r);

	//p表示平面 V表示点
	float GetDistance(XMFLOAT4 p, XMFLOAT3 v);
};




#endif // CAMERA_H