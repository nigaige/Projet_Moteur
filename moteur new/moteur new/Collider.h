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
	
	void(*triggerCallback_)(Collider*) ;

public:
	Collider();
	void isTrigger(bool isTrigger) { isTrigger_ = isTrigger; }
	bool isTrigger() { return isTrigger_; }
	
	void triggerCallback(void(*callback)(Collider*)) { triggerCallback_ = callback; }
	
	void isColliding(Collider* other, D3DXVECTOR3* distance);
	colliderType type() { return type_; }
	void CollisionCallBack(Collider* other);


};

