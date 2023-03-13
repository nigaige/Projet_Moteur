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
	D3DXMatrixTranslation(&mPos, NewPos.x, NewPos.y, NewPos.z);
	UpdateRendu();
}

void Transform::SetvScale(D3DXVECTOR3 NewScale)
{
	D3DXMatrixScaling(&mScale, NewScale.x, NewScale.y, NewScale.z);
	UpdateRendu();
}

void Transform::CreateRotation(float NewRoll, float NewPitch, float NewYaw, bool isRadian = false)
{

	//TODO init quatRot


	if (isRadian) {
		Roll = NewRoll;
		Pitch = NewPitch;
		Yaw = NewYaw;
	}
	else {
		//Converting All to rad
		Roll = DegToRad(NewRoll);
		Pitch = DegToRad(NewPitch);
		Yaw = DegToRad(NewYaw);
	}


	D3DXQUATERNION quat;
	D3DXQuaternionRotationAxis(&quat, &vDir, Roll);
	quatRot *= quat;
	D3DXQuaternionRotationAxis(&quat, &vRight, Pitch);
	quatRot *= quat;
	D3DXQuaternionRotationAxis(&quat, &vUp, Yaw);
	quatRot *= quat;
}



void Transform::SetRotation(float NewRoll, float NewPitch, float NewYaw, bool isRadian = false)
{
	
	CreateRotation(NewRoll, NewPitch, NewYaw, isRadian);
	D3DXMatrixRotationQuaternion(&mRot,&quatRot);

	UpdateRendu();
}
//TODO add Rotation
//TODO set Just roll
//TODO set Just pitch
//TODO set Just yaw
//TODO add roll
//TODO add pitch
//TODO add yaw



void Transform::UpdateRendu()
{
	//TODO Point de Pivot a Mettre
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
