#pragma once
class ColliderManager
{
private:

	std::vector<Collider*> colliderList;
public:
	void manageCollision();
	bool isColliding(Collider* c1, Collider* c2);
	bool collisionSphereSphere(ColliderSphere* c1, ColliderSphere* c2);
	bool collisionCubeCube(ColliderCube* c1, ColliderCube* c2);
	bool collisionSphereCube(ColliderSphere* c1, ColliderCube* c2);



};

