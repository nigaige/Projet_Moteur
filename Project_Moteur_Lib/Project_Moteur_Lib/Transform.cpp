#include "Transform.h"


Transform::Transform()
{

	Roll = 0.0f;
	Pitch = 0.0f;
	Yaw = 0.0f;
	D3DXMatrixIdentity(&mScale);
	D3DXMatrixIdentity(&mPos);
	D3DXMatrixIdentity(&mRot);
}
void Transform::SetvPos(D3DXVECTOR3 NewPos)
{

	vPosition = NewPos;
	D3DXMatrixTranslation(&mPos, vPosition.x, vPosition.y, vPosition.z);
	UpdateRendu();
}

void Transform::SetvScale(D3DXVECTOR3 NewScale)
{

	vScale = NewScale;
	D3DXMatrixScaling(&mScale, vScale.x, vScale.y, vScale.z);
	UpdateRendu();
}

void Transform::SetRotation(float NewRoll, float NewPitch, float NewYaw)
{
	Roll = DegToRad(NewRoll);
	Pitch = DegToRad(NewPitch);
	Yaw = DegToRad(NewYaw);



	D3DXQUATERNION quat;
	D3DXQuaternionRotationAxis(&quat, &vDir, Roll);
	quatRot *= quat;
	D3DXQuaternionRotationAxis(&quat, &vRight, Pitch);
	quatRot *= quat;
	D3DXQuaternionRotationAxis(&quat, &vUp, Yaw);
	quatRot *= quat;


	D3DXMatrixRotationQuaternion(&mRot, &quatRot);

}

void Transform::UpdateRendu()
{
	//Point de Pivot a Mettre
	mRendu = mScale;
	mRendu *= mRot;
	mRendu *= mPos;

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




float Transform::DegToRad(float Angle)
{
	return Angle * (M_PI /180);
}
