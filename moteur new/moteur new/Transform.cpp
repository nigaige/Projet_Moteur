#include "Utils.h"

Transform::Transform(GameObject* gameObject)
{
	gameObject_ = gameObject;
	D3DXMatrixIdentity(&m_Transform_);
	v_scale_.x = 1;
	v_scale_.y = 1;
	v_scale_.z = 1;
	updateScale();
	v_position_.x = 0;
	v_position_.y = 0;
	v_position_.z = 0;
	updatePosition();
	v_position_.x = v_position_.x;
	v_position_.y = v_position_.y;
	v_position_.z = v_position_.z;
	v_forward_ = new FORWARD;
	v_up_ = new UP;
	v_right_ = new RIGHT;
	D3DXMATRIX out;

	D3DXQuaternionIdentity(&q_rotation_);
	D3DXMatrixRotationQuaternion(&m_rotation_, &q_rotation_);

	updateFinal();
}

Transform::~Transform()
{
	//TODO FIX
}

//----------position--------
D3DXVECTOR3 Transform::position()			{return v_position_;}
void Transform::position(D3DXVECTOR3 newPos) { v_position_ = newPos; updatePosition(); }
void Transform::posX(float x)				{ v_position_.x = x; updatePosition(); }
void Transform::posY(float y)				{ v_position_.y = y; updatePosition(); }
void Transform::posZ(float z) { v_position_.z = z; updatePosition(); }
void Transform::updatePosition() {
	D3DXMatrixTranslation(&m_position_, v_position_.x, v_position_.y, v_position_.z);
	toUpdate();
}

//----------Scale-----------
D3DXVECTOR3 Transform::scale()				{ return v_scale_; }
void Transform::scale(D3DXVECTOR3 newPos)		{ v_scale_ = newPos; updateScale();}
void Transform::scaleX(float x)				{ v_scale_.x = x; updateScale(); }
void Transform::scaleY(float y)				{ v_scale_.y = y; updateScale(); }
void Transform::scaleZ(float z)				{ v_scale_.z = z; updateScale(); }
void Transform::updateScale() {
	D3DXMatrixScaling(&m_scale_, v_scale_.x, v_scale_.y, v_scale_.z);
	toUpdate();
}

//---------Rotation---------

D3DXMATRIX Transform::rotation()			{ return m_rotation_; }

void Transform::addPitch(float pitch)
{
	getARotation(NULL, pitch, NULL);
}

void Transform::addRoll(float roll)
{
	getARotation(roll, NULL, NULL);
}

void Transform::addYaw(float yaw)
{
	getARotation(NULL, NULL, yaw);
}

void Transform::addRollPitchYaw(float pitch, float roll, float yaw) {
	getARotation(pitch, roll, yaw);
}

D3DXVECTOR3* Transform::forward()
{
	return v_forward_;
}

D3DXVECTOR3* Transform::right()
{
	return v_right_;
}

D3DXVECTOR3* Transform::up()
{
	return v_up_;
}

D3DXQUATERNION Transform::genRotation(float roll, float pitch, float yaw)
{
	D3DXQUATERNION quat;
	D3DXQUATERNION quatRot;
	D3DXQuaternionIdentity(&quatRot);

	if (roll != NULL) {
		D3DXQuaternionRotationAxis(&quat, v_forward_, roll);
		quatRot *= quat;
	}
	if (pitch != NULL) {
		D3DXQuaternionRotationAxis(&quat, v_right_, pitch);
		quatRot *= quat;
	}
	if (yaw != NULL) {
		D3DXQuaternionRotationAxis(&quat, v_up_, yaw);
		quatRot *= quat;
	}

	return quatRot;
}

void Transform::setARotation(float roll, float pitch, float yaw)
{
	q_rotation_ = genRotation(roll,pitch,yaw);
	D3DXMatrixRotationQuaternion(&m_rotation_, &q_rotation_);
	v_right_->x = m_rotation_._11;
	v_right_->y = m_rotation_._12;
	v_right_->z = m_rotation_._13;
	v_up_->x = m_rotation_._21;
	v_up_->y = m_rotation_._22;
	v_up_->z = m_rotation_._23;
	v_forward_->x = m_rotation_._31;
	v_forward_->y = m_rotation_._32;
	v_forward_->z = m_rotation_._33;
	toUpdate();

}

void Transform::getARotation(float roll, float pitch, float yaw){	

	q_rotation_ *= genRotation(roll, pitch, yaw);
	D3DXMatrixRotationQuaternion(&m_rotation_, &q_rotation_);

	v_right_->x		= m_rotation_._11;
	v_right_->y		= m_rotation_._12;
	v_right_->z		= m_rotation_._13;
	v_up_->x		= m_rotation_._21;
	v_up_->y		= m_rotation_._22;
	v_up_->z		= m_rotation_._23;
	v_forward_->x	= m_rotation_._31;
	v_forward_->y	= m_rotation_._32;
	v_forward_->z	= m_rotation_._33;

	toUpdate();
}


//-------------FINAL------------
D3DXMATRIX* Transform::updateFinal(GameObject* parent){
	if (updated) return &m_TransformWorld_;
	m_Transform_ = m_scale_;
	m_Transform_ *= m_rotation_;
	m_Transform_ *= m_position_;
	m_TransformWorld_ = m_Transform_;
	if (parent != nullptr) {
		m_TransformWorld_ *= *parent->updateTransform();
	}
	updated = true;
	return &m_TransformWorld_;
}

D3DXMATRIX* Transform::displayValue()
{
	return &m_Transform_;
}
D3DXMATRIX* Transform::worldValue()
{
	return &m_TransformWorld_;
}
//-------UTILS---------
std::string Transform::toString()
{
	return "position: " + posToString() + " || rotation: " +rotToString() + " || Scale " + ScaToString() ;
}

std::string Transform::posToString()
{
	return std::string();//TODO
}

std::string Transform::ScaToString()
{
	return std::string();//TODO
}

std::string Transform::rotToString()
{
	return std::string();//TODo
}


