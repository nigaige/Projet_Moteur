#pragma once
#include "Utils.h"

ColliderCube::ColliderCube(D3DXVECTOR3* center, D3DXVECTOR3* size)
{
	type_ = CUBE;
	center_ = center;
	size_ = size;
}
