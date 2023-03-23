#include "Utils.h"

RigidBody::RigidBody()
{
}

void RigidBody::gravity()
{
	*speed += Moteur::s_deltaTime_ * mass_ * DOWN;
}

void RigidBody::update() {
	if (isKinematic_) return;
	gravity();
	transform_->position(transform_->position() + *speed);
}