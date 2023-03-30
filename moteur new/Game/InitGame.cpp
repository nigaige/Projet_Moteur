#include "Utils.h";

InitGame::InitGame(Moteur* moteur)
{
	moteur_ = moteur;
}

void InitGame::update()
{
}

void InitGame::init()
{


	Mesh* meshCube;
	meshCube = moteur_->ImportingModel("./Mesh/cylinder2.x");
	Mesh* anchormesh;
	anchormesh = moteur_->ImportingModel("./Mesh/cubeRose.x");
	Mesh* meshPlayer;
	meshPlayer = moteur_->ImportingModel("./Mesh/BONGUSV2.x");

	GameObject* playerParentRoad = new GameObject();
	GameObject* playerParentRoll = new GameObject(playerParentRoad);
	GameObject* player = new GameObject(playerParentRoll);
	//	GameObject* player = new GameObject();

	GameObject* a[10];
	for (int x = 0; x < 10; ++x) {
		MoveForward* roadcomponent = new MoveForward();

		a[x] = new GameObject();
		a[x]->addComponent(roadcomponent);
		a[x]->addComponent(meshCube);

		a[x]->transform()->addRoll(M_PI * 0.5);
		a[x]->transform()->position((D3DXVECTOR3(-0.5f, -0.f, -0.f)));
		a[x]->transform()->scale(D3DXVECTOR3(2.f, 2.f, 2.f));
		a[x]->transform()->scaleY(5);
		a[x]->transform()->posZ(x * 10);
		moteur_->addGameObject(a[x]);
	}


	player->addComponent(meshPlayer);
	player->transform()->scale(D3DXVECTOR3(0.1f, 0.1f, 0.1f));

	playerParentRoad->addComponent(anchormesh);
	playerParentRoll->addComponent(new PlayerRolling());
	//playerParent->transform()->posY(4.f);
	playerParentRoll->transform()->posY(3.f);
	player->transform()->posY(-0.5f);
	player->addComponent(new playerRoll);
	playerParentRoad->addComponent(new playerRoll);
	moteur_->camera()->addComponent(new playerRoll);

	//moteur->camera()->parent(playerParentRoad);

	moteur_->addGameObject(playerParentRoad);
	moteur_->addGameObject(playerParentRoll);
	moteur_->addGameObject(player);
}
