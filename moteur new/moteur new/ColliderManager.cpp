#pragma once
#include "Utils.h"

void ColliderManager::manageCollision()//TODO change to eat a vector when manageing chunk or tag of collider
{
	int index = 0;
	int size = colliderList.size();
	for (Collider* col : colliderList) {
		if (index = size - 1) break;//last collider of array doesn't check anything else
		for (int i = index+1; i < size; i++) {
			if (isColliding(col, colliderList[i])) {
				col->isColliding(colliderList[i]);
				colliderList[i]->isColliding(col);
			}
		}
		index++;
	}
}

bool ColliderManager::isColliding(Collider* c1, Collider* c2)
{
	//if (dynamic_cast<ColliderSphere>(c1) )




	return false;
}

bool ColliderManager::collisionSphereSphere(ColliderSphere* c1, ColliderSphere* c2)
{
	return false;
}

bool ColliderManager::collisionCubeCube(ColliderCube* c1, ColliderCube* c2)
{
	return false;
}

bool ColliderManager::collisionSphereCube(ColliderSphere* c1, ColliderCube* c2)
{
	return false;
}
