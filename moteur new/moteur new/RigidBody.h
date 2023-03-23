#pragma once
class RigidBody:public Component
{
private:
	bool isKinematic_ = false;
	float mass_ = 1.0f;
	D3DXVECTOR3* speed = new D3DXVECTOR3(0, 0, 0);

public:
	RigidBody();
	bool isKinematic()					{ return isKinematic_; }
	void isKinematic(bool isKinematic)	{ isKinematic_ = isKinematic; }



	void gravity();
	void update();
	//TODO setter/getter



};

