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
