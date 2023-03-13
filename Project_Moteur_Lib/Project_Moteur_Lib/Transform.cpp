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


#pragma region rotation

void Transform::CreateRotation(float NewRoll, float NewPitch, float NewYaw, bool isRadian)
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
	
	D3DXQuaternionRotationAxis(&quat, &vDir, Roll);
	quatRot *= quat;
	D3DXQuaternionRotationAxis(&quat, &vRight, Pitch);
	quatRot *= quat;
	D3DXQuaternionRotationAxis(&quat, &vUp, Yaw);
	quatRot *= quat;
}

void Transform::SetRotation(float NewRoll, float NewPitch, float NewYaw, bool isRadian)
{
	CreateRotation(NewRoll, NewPitch, NewYaw, isRadian);
	D3DXMatrixRotationQuaternion(&mRot,&quatRot);

	UpdateRendu();
}
void Transform::SetPitch(float Angle, bool isRadian)
{
	if (isRadian) {
		Pitch = Angle;
	}
	else {
		//Converting to rad
		Pitch = DegToRad(Angle);
	}
	D3DXQuaternionRotationAxis(&quat, &vRight, Pitch);
	quatRot *= quat;
	UpdateRendu();
}
void Transform::SetRoll(float Angle, bool isRadian)
{
	if (isRadian) {
		Roll = Angle;
	}
	else {
		//Converting to rad
		Roll = DegToRad(Angle);
	}
	D3DXQuaternionRotationAxis(&quat, &vDir, Roll);
	quatRot *= quat;
	UpdateRendu();
}
void Transform::SetYaw(float Angle, bool isRadian)
{
	if (isRadian) {
		Yaw = Angle;
	}
	else {
		//Converting to rad
		Yaw = DegToRad(Angle);
	}
	D3DXQuaternionRotationAxis(&quat, &vUp, Yaw);
	quatRot *= quat;
	UpdateRendu();
}

void Transform::addRotation(float NewYaw, float NewPitch, float NewRoll, bool isRadian)
{
	D3DXQUATERNION Qa;
	CreateRotation(NewRoll, NewPitch, NewYaw, isRadian);
	D3DXQuaternionRotationMatrix(&Qa, &mRot);
	quatRot *= Qa;
	D3DXMatrixRotationQuaternion(&mRot, &quatRot);

	UpdateRendu();

}
void Transform::AddPitch(float Angle, bool isRadian)
{
	float newPitch;
	if (isRadian) {
		 newPitch = Angle;
	}
	else {
		//Converting to rad
		newPitch = DegToRad(Angle);
	}
	Pitch += newPitch;
	D3DXQuaternionRotationAxis(&quat, &vRight, Pitch);
	quatRot *= quat;
	UpdateRendu();
}
void Transform::AddRoll(float Angle, bool isRadian)
{
	float newRoll;
	if (isRadian) {
		newRoll = Angle;
	}
	else {
		//Converting to rad
		newRoll = DegToRad(Angle);
	}
	Roll += newRoll;
	D3DXQuaternionRotationAxis(&quat, &vDir, Roll);
	quatRot *= quat;
	UpdateRendu();
}
void Transform::AddYaw(float Angle, bool isRadian)
{
	float newYaw;
	if (isRadian) {
		newYaw = Angle;
	}
	else {
		//Converting to rad
		newYaw = DegToRad(Angle);
	}
	Yaw += newYaw;
	D3DXQuaternionRotationAxis(&quat, &vUp, Yaw);
	quatRot *= quat;
	UpdateRendu();
}
#pragma endregion
#pragma region position
void Transform::SetvPos(D3DXVECTOR3 NewPos)
{
	D3DXMatrixTranslation(&mPos, NewPos.x, NewPos.y, NewPos.z);
	UpdateRendu();
}

D3DXVECTOR3 Transform::GetvPos()
{
	return vPosition;
}

float Transform::GetvPosX()
{
	return vPosition.x;
}
float Transform::GetvPosY()
{
	return vPosition.y;
}
float Transform::GetvPosZ()
{
	return vPosition.z;
}
#pragma endregion

#pragma region MyRegion
void Transform::SetvScale(D3DXVECTOR3 NewScale)
{
	D3DXMatrixScaling(&mScale, NewScale.x, NewScale.y, NewScale.z);
	UpdateRendu();
}
D3DXVECTOR3 Transform::GetvScale()
{
	return vScale;
}
float Transform::GetvScaleX()
{
	return vScale.x;
}
float Transform::GetvScaleY()
{
	return vScale.y;
}
float Transform::GetvScaleZ()
{
	return vScale.z;
}

#pragma endregion


void Transform::UpdateRendu()
{
	//TODO Point de Pivot a Mettre
	mRendu = mScale;
	mRendu *= mRot;
	mRendu *= mPos;

}

D3DXVECTOR3 Transform::GetvRot()
{
	D3DXQUATERNION getRot;
	D3DXQuaternionRotationMatrix (&getRot, &mRot);
	D3DXVECTOR3(DegToRad(getRot.x), DegToRad(getRot.y), DegToRad(getRot.z));
	return ;
}



D3DXMATRIX Transform::GetRendu()
{
	return mRendu;
}

float Transform::DegToRad(float Angle)
{
	return Angle * (M_PI /180);
}

float Transform::RadToDeg(float Rad)
{
	return Rad * (180 /M_PI);
}

