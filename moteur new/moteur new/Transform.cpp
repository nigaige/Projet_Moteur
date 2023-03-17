#include "Transform.h"

Transform::Transform()
{
	D3DXMatrixIdentity(&m_Transform_);
	v_scale_.x = 1;
	v_scale_.y = 1;
	v_scale_.z = 1;
	updateScale();
	v_position_.x = 0;
	v_position_.y = 0;
	v_position_.z = 0;
	updatePosition();
	pitch_ = 0;
	yaw_ = 0;
	roll_ = 0;
	updateRotation();
}

Transform::~Transform()
{

}

//----------position--------
D3DXVECTOR3 Transform::position()			{return v_position_;}
void Transform::position(D3DVECTOR newPos)	{ v_position_ = newPos; updatePosition();}
void Transform::posX(float x)				{ v_position_.x = x; updatePosition(); }
void Transform::posY(float y)				{ v_position_.y = y; updatePosition(); }
void Transform::posZ(float z)				{ v_position_.z = z; updatePosition(); }
void Transform::updatePosition() {
	D3DXMatrixTranslation(&m_position_, v_position_.x, v_position_.y, v_position_.z);
	updateFinal();
}

//----------Scale-----------
D3DXVECTOR3 Transform::scale()				{ return v_scale_; }
void Transform::scale(D3DVECTOR newPos)		{ v_scale_ = newPos; updateScale();}
void Transform::scaleX(float x)				{ v_scale_.x = x; updateScale(); }
void Transform::scaleY(float y)				{ v_scale_.y = y; updateScale(); }
void Transform::scaleZ(float z)				{ v_scale_.z = z; updateScale(); }
void Transform::updateScale() {
	D3DXMatrixScaling(&m_scale_, v_scale_.x, v_scale_.y, v_scale_.z);
	updateFinal();
}

//---------Rotation---------

D3DXMATRIX Transform::rotation()			{ return m_rotation_; }
void Transform::rotation(D3DXMATRIX newrot) { m_rotation_ = newrot; updateRotation();}
void Transform::roll(float newRoll)			{ roll_ = newRoll; updateRotation();}
void Transform::yaw(float newYaw)			{ yaw_ = newYaw; updateRotation();}
void Transform::pitch(float newPitch)		{ pitch_ = newPitch; updateRotation();}
float Transform::roll()						{return roll_;}
float Transform::yaw()						{return yaw_;}
float Transform::pitch()					{return pitch_;}

void Transform::updateRotation(){
	m_rotation_ = *getARotation(roll_, pitch_, yaw_);
	updateFinal();
}

D3DXMATRIX* Transform::getARotation(float roll, float pitch, float yaw, bool isRadian){	
	D3DXQUATERNION quat;
	D3DXMATRIX out;
	if (isRadian) {
		D3DXQuaternionRotationYawPitchRoll(&quat, roll, pitch, yaw);
	} else {
		D3DXQuaternionRotationYawPitchRoll(&quat,Utils::DegToRad(roll), Utils::DegToRad(pitch), Utils::DegToRad(yaw));
	}
	D3DXMatrixRotationQuaternion(&out, &quat);
	return &out;
}


//-------------FINAL------------
void Transform::updateFinal(){
	m_Transform_ = m_scale_;
	m_Transform_ *= m_rotation_;
	m_Transform_ *= m_position_;
}

D3DXMATRIX* Transform::displayValue()
{
	return &m_Transform_;
}
//-------UTILS---------
std::string Transform::toString()
{
	return std::string();
}

