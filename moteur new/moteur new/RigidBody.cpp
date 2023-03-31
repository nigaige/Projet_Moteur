#include "Utils.h"

RigidBody::RigidBody()
{
	type_ = RIGIDBODY;
}

RigidBody::~RigidBody()
{
	delete speed_;
}

void RigidBody::speed(D3DXVECTOR3* speed)
{
	*speed_ = *speed;

}
void RigidBody::applyGravity()
{
	*speed_ += Moteur::s_deltaTime_ * mass_ * gravity_ * DOWN ;
}

void RigidBody::update() {
	if (isKinematic_) return;
	if (hasGravity_) applyGravity();
	transform_->position(transform_->position() + *speed_);
}