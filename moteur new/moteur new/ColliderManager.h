#pragma once
class ColliderManager
{
private:

	std::vector<Collider*> colliderList;
public:
	void addCollider(Collider* col);
	ColliderManager();
	~ColliderManager();
	void manageCollision();
	D3DXVECTOR3* isColliding(Collider* c1, Collider* c2);
	D3DXVECTOR3* collisionSphereSphere(ColliderSphere* c1, ColliderSphere* c2);
	bool collisionCubeCube(ColliderCube* c1, ColliderCube* c2);
	D3DXVECTOR3* collisionSphereCube(ColliderSphere* c1, ColliderCube* c2);



};

