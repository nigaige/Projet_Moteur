#include "Utils.h"

RigidBody::RigidBody()
{
}

void RigidBody::speed(D3DXVECTOR3* speed)
{
	*speed_ = *speed;

}
void RigidBody::gravity()
{
	*speed_ += Moteur::s_deltaTime_ * mass_ * DOWN;
}

void RigidBody::update() {
	if (isKinematic_) return;
	gravity();
	transform_->position(transform_->position() + *speed_);
}