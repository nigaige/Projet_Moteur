#pragma once



enum colliderType
{
	SPHERE,
	CUBE
};

class Collider : public Component
{
protected:
	colliderType type_;
	bool isTrigger_ = false;
	//triggerCallback function //TODO
	//CollisionCallBack
public:
	void isColliding(Collider* other, D3DXVECTOR3* distance);
	colliderType type() { return type_; }

};

