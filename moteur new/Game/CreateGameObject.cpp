#include "Utils.h"

GameObject* CreateGameObject::Wall(Mesh wallMesh, Shader* wallShader, D3DXVECTOR3* position, D3DXVECTOR3* rotation)
{
	GameObject* Wall = new GameObject();
	ColliderCube* BoxWallCollider = new ColliderCube(new D3DXVECTOR3(0, 0, 0), new D3DXVECTOR3(1, 1, 1));
	RigidBody* rbWall = new RigidBody();

	wallMesh.shader(wallShader);

	rbWall->isKinematic(true);
	rbWall->hasGravity(false);

	Wall->addComponent(&wallMesh);
	Wall->addComponent(rbWall);
	Wall->addComponent(BoxWallCollider);

	Wall->transform()->position(*position);
	Wall->transform()->addRollPitchYaw(rotation->x, rotation->y, rotation->z);
	Wall->transform()->scale(D3DXVECTOR3(1.5f, 4.f, 0.5f));

	return Wall;
}

GameObject* CreateGameObject::Floor(Mesh floorMesh)
{
	GameObject* floor = new GameObject();
	floor->addComponent(&floorMesh);

	floor->transform()->addRoll(M_PI * 0.5);
	floor->transform()->position((D3DXVECTOR3(0.f, -0.f, -0.f)));
	floor->transform()->scale(D3DXVECTOR3(2.f, 2.f, 2.f));
	floor->transform()->scaleY(5);

	return floor;
}

