#pragma once
class ColliderCube: public Collider
{
private:
	D3DXVECTOR3* center_ = new D3DXVECTOR3(0, 0, 0);
	float size_[3] = { 1.0f,1.0f,1.0f };
	std::vector<triangle> faces_;
	void genTriangle();
public:
	ColliderCube(D3DXVECTOR3* center, D3DXVECTOR3* size);

	D3DXVECTOR3* center() { return center_; }
	float* size() { return size_; }
	std::vector<triangle> faces() { return faces_; }

};

