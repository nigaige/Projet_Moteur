#include "Transform.h"


void Transform::SetvPos(D3DXVECTOR3 NewPos)
{

	vPosition = NewPos;
	UpdateRendu();
}

void Transform::SetvScale(D3DXVECTOR3 NewScale)
{

	vScale = NewScale;
	UpdateRendu();
}





void Transform::UpdateRendu()
{


}


D3DXVECTOR3 Transform::GetvScale()
{
	return vScale;
}

D3DXVECTOR3 Transform::GetvPos()
{
	return vPosition;
}

D3DXMATRIX Transform::GetRendu()
{
	return mRendu;
}

void Transform::Rotate(float NewRoll,float NewPitch,float NewYaw )
{
	Roll = DegToRad(NewRoll);
	Pitch = DegToRad(NewPitch);
	Yaw = DegToRad(NewYaw);



	
	D3DXQuaternionRotationAxis(&quat, m_vDir, Roll);
	quatRot *= quat;
	D3DXQuaternionRotationAxis(&quat, m_vRight, Pitch);
	quatRot *= quat;
	D3DXQuaternionRotationAxis(&quat, m_vUp, Yaw);
	quatRot *= quat;
}


float Transform::DegToRad(float Angle)
{
	return Angle * (M_PI /180);
}
