#include "Utils.h"

Wall::Wall(Moteur* moteur, Shader* color, Mesh* WallMesh)
{
	GameObject* Wall = new GameObject();

	WallMesh->shader(color);

	RigidBody* rbWall = new RigidBody();
	rbWall->isKinematic(true);
	rbWall->hasGravity(false);

	ColliderCube* BoxWallCollider = new ColliderCube(new D3DXVECTOR3(0, 0, 0), new D3DXVECTOR3(1, 1, 1));


	Wall->addComponent(WallMesh);
	Wall->addComponent(rbWall);
	Wall->addComponent(BoxWallCollider);

	Wall->transform()->position((D3DXVECTOR3(0.f, 4.f, 0.f)));
	//Wall_->transform()->addRollPitchYaw(0.f, 0.f, 0.f);
	Wall->transform()->scale((D3DXVECTOR3(1.5f, 4.f, 0.5f)));

	moteur->colliderManager()->addCollider(BoxWallCollider);
	moteur->addGameObject(Wall);
}

Wall::~Wall(){}

void Wall::update() 
{
	
}

