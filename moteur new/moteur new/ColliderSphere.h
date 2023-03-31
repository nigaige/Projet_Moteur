#pragma once
class ColliderSphere : public Collider
{
private:
	D3DXVECTOR3* center_ = new D3DXVECTOR3(0,0,0);
	float radius_ = 1;
public:

	ColliderSphere(D3DXVECTOR3* center, float radius);
	~ColliderSphere();

	D3DXVECTOR3* center() { return center_; }
	void center(D3DXVECTOR3 center) { *center_ = center; }
	
	float radius() { return radius_; }
	void radius(float radius) { radius_ = radius; }

};

