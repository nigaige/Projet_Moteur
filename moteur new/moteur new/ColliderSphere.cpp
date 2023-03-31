#pragma once
#include "Utils.h"


ColliderSphere::ColliderSphere(D3DXVECTOR3 *center, float radius)
{
	type_ = SPHERE;

	*center_ = *center;
	radius_ = radius;
}

ColliderSphere::~ColliderSphere()
{
	delete center_;
}
