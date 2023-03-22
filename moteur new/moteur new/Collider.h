#pragma once



enum colliderType
{
	SPHERE,
	CUBE
};

class Collider
{
protected:
	colliderType type;
	bool isTrigger = false;
	//triggerCallback function //TODO
	//CollisionCallBack
public:
	void isColliding(Collider* other);

};

