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

void Transform::Rotate(float NewYaw, float NewPitch, float NewRoll)
{
	Yaw = NewYaw;
	Pitch = NewPitch;
	Roll = NewRoll;

}
