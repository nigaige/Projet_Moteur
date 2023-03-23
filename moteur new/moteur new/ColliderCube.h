#pragma once
class ColliderCube: public Collider
{
private:
	D3DXVECTOR3* center_ = new D3DXVECTOR3(0, 0, 0);
	D3DXVECTOR3* size_ = new D3DXVECTOR3(1, 1, 1);
public:
	ColliderCube(D3DXVECTOR3* center, D3DXVECTOR3* size);
};

