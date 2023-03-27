#pragma once
class RigidBody:public Component
{
private:
	bool isKinematic_ = false;
	bool hasGravity_ = true;
	float mass_ = 1.0f;
	D3DXVECTOR3* speed_ = new D3DXVECTOR3(0, 0, 0);
	float gravity_  = 0.0008f;


public:
	RigidBody();
	bool isKinematic()					{ return isKinematic_; }
	void isKinematic(bool isKinematic)	{ isKinematic_ = isKinematic; }
	bool hasGravity()					{ return hasGravity_; }
	void hasGravity(bool hasGravity)	{ hasGravity_ = hasGravity; }
	float gravity()						{ return gravity_; }
	void gravity(float gravity)			{ gravity_ = gravity; }

	D3DXVECTOR3* speed() { return speed_; }
	void speed(D3DXVECTOR3* speed);

	void applyGravity();
	void update();



};

