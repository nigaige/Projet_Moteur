#pragma once
#include "Utils.h"

void Collider::isColliding(Collider* other, D3DXVECTOR3* distance)
{
	transform_->position(transform_->position() + *distance);
}
