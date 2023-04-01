#pragma once
#include "Utils.h"

void ColliderManager::addCollider(Collider* col)
{
	colliderList.push_back(col);
}

ColliderManager::ColliderManager()
{
}

ColliderManager::~ColliderManager()
{
	for (Collider* col : colliderList) delete col;
	colliderList.clear();
}

void ColliderManager::manageCollision()//TODO change to eat a vector when manageing chunk or tag of collider
{
	//TODO check doubl kinematic
	int index = 0;
	size_t size = colliderList.size();
	D3DXVECTOR3* colValue = nullptr;
	for (Collider* col : colliderList) {
		if (index == size - 1) break;//last collider of array doesn't check anything else
		for (int i = index+1; i < size; i++) {
			
			if (col->gameObject()->rb()->isKinematic()) {
				colValue = isColliding(colliderList[i], col);
			}else {
				colValue = isColliding(col, colliderList[i]);
			}
			if (colValue != nullptr) {
				if (col->isTrigger() || colliderList[i]->isTrigger()) {//case with at least a trigger
					col->CollisionCallBack(colliderList[i]);
					colliderList[i]->CollisionCallBack(col);
				}
				else {//case with both collider
					colliderList[i]->isColliding(col, colValue);
					*colValue = -*colValue;
					col->isColliding(colliderList[i], colValue);
				}
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
	else if ((c1->type() == SPHERE || c2->type() == SPHERE) && (c1->type() == CUBE || c2->type() == CUBE)) {
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
		ColliderCube* cube1 = new ColliderCube();
		*cube1 = *Utils::castToType<ColliderCube>(c1);
		ColliderCube* cube2 = new ColliderCube();
		*cube2 = *Utils::castToType<ColliderCube>(c2);
		//test if cube colliede each other
		if (collisionCubeCube(cube1,cube2)) {
			if (cube1->isTrigger() || cube2->isTrigger())return new D3DXVECTOR3();



			//If yes, do a raycast from cube 1 toward it's direction

			D3DXVECTOR3 dir;
			D3DXVec3Normalize(&dir, cube1->gameObject()->rb()->speed());
			dir *= -10;
			for (triangle tri: cube2->faces()) {
				D3DXVECTOR3* pintersect = new D3DXVECTOR3();
				D3DXVECTOR3 point = *cube1->center() + cube1->gameObject()->transform()->position();
				float* dist = new float(0);
				if (Utils::raycast(
					&point,
					&dir ,
					Utils::offsetTirangle(tri, cube2->gameObject()->transform()->position()),
					pintersect,
					NULL,
					dist,
					true
				)) {
					D3DXVECTOR3* N = new D3DXVECTOR3();
					D3DXVec3Normalize (N,Utils::triangleNormal(&tri));
					*N = - *N * D3DXVec3Length (cube1->gameObject()->rb()->speed());
					return N;
				}
			}

			D3DXVec3Normalize(&dir, cube2->gameObject()->rb()->speed());
			dir *= -10;
			for (triangle tri : cube1->faces()) {
				D3DXVECTOR3* pintersect = new D3DXVECTOR3();
				D3DXVECTOR3 point = *cube2->center() + cube2->gameObject()->transform()->position();
				float* dist = new float(0);
				if (Utils::raycast(
					&point,
					&dir,
					Utils::offsetTirangle(tri, cube1->gameObject()->transform()->position()),
					pintersect,
					NULL,
					dist,
					true
				)) {
					D3DXVECTOR3* N = new D3DXVECTOR3();
					D3DXVec3Normalize(N, Utils::triangleNormal(&tri));
					*N = -*N * D3DXVec3Length(cube2->gameObject()->rb()->speed());


					return N;
				}
			}
		}
		return nullptr;
	}




	return nullptr;
}

D3DXVECTOR3* ColliderManager::collisionSphereSphere(ColliderSphere* c1, ColliderSphere* c2)
{
	//TODO Make smooth
	D3DXVECTOR3 pos1 = c1->transform()->position() + *c1->center();
	D3DXVECTOR3 pos2 = c2->transform()->position() + *c2->center();
	float radSum = c1->radius() + c2->radius();
	float dist = Utils::distance(pos1, pos2);//IMprove calcul
	if (dist <= radSum) {
		D3DXVECTOR3 result = pos1 - pos2;
		D3DXVec3Normalize(&result, &result);
		result = result * (radSum - dist);
		return &result;
	}else {
		return nullptr;
	}
}

bool ColliderManager::collisionCubeCube(ColliderCube* c1, ColliderCube* c2)
{
	float ra, rb;
	float R[3][3];
	float AbsR[3][3];




	R[0][0] = D3DXVec3Dot(c1->transform()->up(), c2->transform()->up());
	R[0][1] = D3DXVec3Dot(c1->transform()->up(), c2->transform()->forward());
	R[0][2] = D3DXVec3Dot(c1->transform()->up(), c2->transform()->right());
	R[1][0] = D3DXVec3Dot(c1->transform()->forward(), c2->transform()->up());
	R[1][1] = D3DXVec3Dot(c1->transform()->forward(), c2->transform()->forward());
	R[1][2] = D3DXVec3Dot(c1->transform()->forward(), c2->transform()->right());
	R[2][0] = D3DXVec3Dot(c1->transform()->right(), c2->transform()->up());
	R[2][1] = D3DXVec3Dot(c1->transform()->right(), c2->transform()->forward());
	R[2][2] = D3DXVec3Dot(c1->transform()->right(), c2->transform()->right());


	D3DXVECTOR3 t = (*c2->center() + c2->transform()->position()) - (*c1->center() + c1->transform()->position());
	t = D3DXVECTOR3(
		D3DXVec3Dot(&t, c1->transform()->up()),
		D3DXVec3Dot(&t, c1->transform()->forward()),
		D3DXVec3Dot(&t, c1->transform()->right())
	);

	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			AbsR[i][j] = abs(R[i][j]) + EPSILON;

	// Test axes L = A0, L = A1, L = A2
	for (int i = 0; i < 3; i++) {
		ra = c1->size()[i];
		rb = c2->size()[0] * AbsR[i][0] + c2->size()[1] * AbsR[i][1] + c2->size()[2] * AbsR[i][2];
		if (abs(t[i]) > ra + rb) return false;
	}
	//Test axes L = B0, L = B1, L = B2
	for (int i = 0; i < 3; i++) {
		ra = c1->size()[0] * AbsR[0][i] + c1->size()[1] * AbsR[1][i] + c1->size()[2] * AbsR[2][i];
		rb = c2->size()[i];
		if (abs(t[0] * R[0][i] + t[1] * R[1][i] + t[2] * R[2][i]) > ra + rb) return false;
	}
	// Test axis L = A0 x B0
	ra = c1->size()[1] * AbsR[2][0] + c1->size()[2] * AbsR[1][0];
	rb = c2->size()[1] * AbsR[0][2] + c2->size()[2] * AbsR[0][1];
	if (abs(t[2] * R[1][0] - t[1] * R[2][0]) > ra + rb) return false;
	// Test axis L = A0 x B1
	ra = c1->size()[1] * AbsR[2][1] + c1->size()[2] * AbsR[1][1];
	rb = c2->size()[0] * AbsR[0][2] + c2->size()[2] * AbsR[0][0];
	if (abs(t[2] * R[1][1] - t[1] * R[2][1]) > ra + rb) return false;
	// Test axis L = A0 x B2
	ra = c1->size()[1] * AbsR[2][2] + c1->size()[2] * AbsR[1][2];
	rb = c2->size()[0] * AbsR[0][1] + c2->size()[1] * AbsR[0][0];
	if (abs(t[2] * R[1][2] - t[1] * R[2][2]) > ra + rb) return false;
	// Test axis L = A1 x B0
	ra = c1->size()[0] * AbsR[2][0] + c1->size()[2] * AbsR[0][0];
	rb = c2->size()[1] * AbsR[1][2] + c2->size()[2] * AbsR[1][1];


	if (abs(t[0] * R[2][0] - t[2] * R[0][0]) > ra + rb) return false;
	// Test axis L = A1 x B1
	ra = c1->size()[0] * AbsR[2][1] + c1->size()[2] * AbsR[0][1];
	rb = c2->size()[0] * AbsR[1][2] + c2->size()[2] * AbsR[1][0];
	if (abs(t[0] * R[2][1] - t[2] * R[0][1]) > ra + rb) return false;
	// Test axis L = A1 x B2
	ra = c1->size()[0] * AbsR[2][2] + c1->size()[2] * AbsR[0][2];
	rb = c2->size()[0] * AbsR[1][1] + c2->size()[1] * AbsR[1][0];
	if (abs(t[0] * R[2][2] - t[2] * R[0][2]) > ra + rb) return false;
	// Test axis L = A2 x B0
	ra = c1->size()[0] * AbsR[1][0] + c1->size()[1] * AbsR[0][0];
	rb = c2->size()[1] * AbsR[2][2] + c2->size()[2] * AbsR[2][1];
	if (abs(t[1] * R[0][0] - t[0] * R[1][0]) > ra + rb) return false;
	// Test axis L = A2 x B1
	ra = c1->size()[0] * AbsR[1][1] + c1->size()[1] * AbsR[0][1];
	rb = c2->size()[0] * AbsR[2][2] + c2->size()[2] * AbsR[2][0];
	if (abs(t[1] * R[0][1] - t[0] * R[1][1]) > ra + rb) return false;
	// Test axis L = A2 x B2
	ra = c1->size()[0] * AbsR[1][2] + c1->size()[1] * AbsR[0][2];
	rb = c2->size()[0] * AbsR[2][1] + c2->size()[1] * AbsR[2][0];
	if (abs(t[1] * R[0][2] - t[0] * R[1][2]) > ra + rb) return false;
	// Since no separating axis is found, the OBBs must be intersecting

	return true;
}

D3DXVECTOR3* ColliderManager::collisionSphereCube(ColliderSphere* c1, ColliderCube* c2)
{
	return nullptr;
}
