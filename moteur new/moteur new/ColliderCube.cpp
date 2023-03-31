#pragma once
#include "Utils.h"

void ColliderCube::genTriangle()
{
	D3DXVECTOR3 A = *center_ + D3DXVECTOR3(size_[0], size_[1], size_[2]);
	D3DXVECTOR3 B = *center_ + D3DXVECTOR3(size_[0], size_[1], -size_[2]);
	D3DXVECTOR3 C = *center_ + D3DXVECTOR3(size_[0], -size_[1], size_[2]);
	D3DXVECTOR3 D = *center_ + D3DXVECTOR3(size_[0], -size_[1], -size_[2]);
	D3DXVECTOR3 E = *center_ + D3DXVECTOR3(-size_[0], size_[1], size_[2]);
	D3DXVECTOR3 F = *center_ + D3DXVECTOR3(-size_[0], size_[1], -size_[2]);
	D3DXVECTOR3 G = *center_ + D3DXVECTOR3(-size_[0], -size_[1], size_[2]);
	D3DXVECTOR3 H = *center_ + D3DXVECTOR3(-size_[0], -size_[1], -size_[2]);
	faces_.push_back({ A,E,G });
	faces_.push_back({ G,C,A });
	faces_.push_back({ E,G,H });
	faces_.push_back({ H,F,E });
	faces_.push_back({ H,F,B });
	faces_.push_back({ B,D,H });
	faces_.push_back({ B,D,C });
	faces_.push_back({ C,A,B });
	faces_.push_back({ A,E,F });
	faces_.push_back({ F,B,A });
	faces_.push_back({ C,G,H });
	faces_.push_back({ H,D,C });
}

ColliderCube::ColliderCube(D3DXVECTOR3* center, D3DXVECTOR3* size)
{
	type_ = CUBE;
	*center_ = *center;
	size_[0] = size->x;
	size_[1] = size->y; 
	size_[2] = size->z;
	genTriangle();
}
ColliderCube::~ColliderCube()
{
	delete center_;
}
;



