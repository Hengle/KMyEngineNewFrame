//******************************************************************************************************************************************************************************************
// ʵ�����������ܣ�1.�ӽǾ��� -> �����Ҫ�ƶ���ĳһ�㡢���ڵ����µ����ᳯ������Ҫ���ӽǱ任
//								 �õ��ĺ�����LookAt()...UpdateViewMatrix()
//				   2.ͶӰ���� -> ����ͶӰ��ز�����Զ��ƽ�桢�ӽǴ�С��ͶӰ�泤�����ͶӰ����
//
// ��ʵ������������������ģ��ǲ����ڵģ���Ψһ���������ȥ�������Ǽ�������ı仯,ȷ�������λ�ã�������һ�㣬������Ȼ���ƶ��������������ʵ����ͨ�������������Ŀ�����ƶ�����������������壡
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

	// ��á����������λ�á�������ز���
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

	// ���ͶӰ����ƽ��ͷ�������Ϣ
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

	// ����ӽ� ͶӰ����
	XMMATRIX View()const;
	XMMATRIX Proj()const;
	XMMATRIX ViewProj()const;
	

	// ����ͶӰ��ز���
	void SetLens(float fovY, float aspect, float zn, float zf);

	// ͨ��λ��+�۲���������ӽǾ����������������λ��+����������,Ҳ����˵�ҿ����ֶ���������
	void LookAt(FXMVECTOR pos, FXMVECTOR target, FXMVECTOR worldUp);
	void LookAt(const XMFLOAT3& pos, const XMFLOAT3& target, const XMFLOAT3& up);	

	// ��������
	void Strafe(float d);						 //����ƽ��
	virtual void Walk(float d);		             //ǰ������
	virtual void Pitch(float angle);             //���µ�ͷ
	virtual void RotateY(float angle);           //����ҡͷ

	// After modifying camera position/orientation, call to rebuild the view matrix.
	// ���޸��������λ�û��򣬸����ӽǾ���
	void UpdateViewMatrix();

protected:

	// Camera coordinate system with coordinates relative to world space.
	// ��������ϵ�£��������ĺ��Ĳ�����λ�á���ǰ�����������-->�����������յ��ӽǱ任����
	XMFLOAT3 mPosition;
	XMFLOAT3 mRight;
	XMFLOAT3 mUp;
	XMFLOAT3 mLook;

	// Cache frustum properties.
	// ͶӰ��ز�����Զ��ƽ�桢�ӽǴ�С��ͶӰ�泤���
	float mNearZ;         
	float mFarZ;
	float mAspect;
	float mFovY;
	float mNearWindowHeight;
	float mFarWindowHeight;

	// Cache View/Proj matrices.
	// �ӽǾ���ͶӰ����
	XMFLOAT4X4 mView;
	XMFLOAT4X4 mProj;
};


//ƽ��ͷ�壬��6��ƽ���ʾ���Һ���һ����Χ�к�ƽ��ͷ��İ˸�����
struct Frustum
{
	XMFLOAT4 LeftPlane;
	XMFLOAT4 RightPlane;
	XMFLOAT4 TopPlane;
	XMFLOAT4 BottomPlane;
	XMFLOAT4 NearPlane;
	XMFLOAT4 FarPlane;

	//��ȡƽ��ͷ��6��ƽ��
	void extractFromMatrix(CXMMATRIX& matrix);

	bool TestPoint(const XMFLOAT3 point);
	bool TestSphere(const XMFLOAT3 Pos, float r);

	//p��ʾƽ�� V��ʾ��
	float GetDistance(XMFLOAT4 p, XMFLOAT3 v);
};




#endif // CAMERA_H