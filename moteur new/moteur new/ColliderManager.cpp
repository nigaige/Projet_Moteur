#pragma once
#include "Utils.h"

void ColliderManager::addCollider(Collider* col)
{
	colliderList.push_back(col);
}

void ColliderManager::manageCollision()//TODO change to eat a vector when manageing chunk or tag of collider
{
	//TODO check doubl kinematic
	int index = 0;
	int size = colliderList.size();
	for (Collider* col : colliderList) {
		if (index == size - 1) break;//last collider of array doesn't check anything else
		for (int i = index+1; i < size; i++) {
			D3DXVECTOR3* colValue = isColliding(col, colliderList[i]);
			if (colValue != nullptr) {
				//TODO deal with kinematic
				col->isColliding(colliderList[i], colValue);
				colliderList[i]->isColliding(col, colValue);
			}
		}
		index++;
	}
}

D3DXVECTOR3* ColliderManager::isColliding(Collider* c1, Collider* c2)
{
	if (c1->type() == SPHERE && c2->type() == SPHERE) {
		return collisionSphereSphere(
			Utils::castToType<ColliderSphere>(c1),
			Utils::castToType<ColliderSphere>(c2)
		);
	}
	else if (c1->type() == SPHERE || c2->type() == SPHERE && c1->type() == CUBE || c2->type() == CUBE) {
		if (c1->type() == SPHERE) {
			return collisionSphereCube(
				Utils::castToType<ColliderSphere>(c1),
				Utils::castToType<ColliderCube>(c2)
			);
		}else {
			return collisionSphereCube(
				Utils::castToType<ColliderSphere>(c2),
				Utils::castToType<ColliderCube>(c1)
			);
		}
	}
	else if (c1->type() == CUBE && c2->type() == CUBE) {
		return collisionCubeCube(
			Utils::castToType<ColliderCube>(c1),
			Utils::castToType<ColliderCube>(c2)
		);
	}




	return nullptr;
}

D3DXVECTOR3* ColliderManager::collisionSphereSphere(ColliderSphere* c1, ColliderSphere* c2)
{
	D3DXVECTOR3 pos1 = c1->transform()->position() + *c1->center();
	D3DXVECTOR3 pos2 = c2->transform()->position() + *c2->center();
	float radSum = c1->radius() + c2->radius();
	float dist = Utils::distance(pos1, pos2);
	if (dist <= radSum * radSum) {
		D3DXVECTOR3 result = pos1 - pos2;
		D3DXVec3Normalize(&result, &result);
		result = result * (radSum - dist);
		return &result;
	}else {
		return nullptr;
	}
}

D3DXVECTOR3* ColliderManager::collisionCubeCube(ColliderCube* c1, ColliderCube* c2)
{
	return nullptr;
}

D3DXVECTOR3* ColliderManager::collisionSphereCube(ColliderSphere* c1, ColliderCube* c2)
{
	return nullptr;
}
