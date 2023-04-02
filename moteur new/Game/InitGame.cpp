#include "Utils.h";

InitGame::InitGame(Moteur* moteur)
{
	moteur_ = moteur;
	camera_ = moteur_->camera();

	camera_->transform()->addRollPitchYaw(0.f, 0.f, 0.f);
	camera_->transform()->position(D3DXVECTOR3(0.f, -7.f, 20.f));
	
	initLevel();
	initGo();
}

void InitGame::initLevel()
{
	levelCreator = new LevelDesigner();
	levelCreator->CreateSection("./ImportScript/SecondSection.txt");
	levelCreator->CreateSection("./ImportScript/ThirdSection.txt");
	
	for (GameObject* go : levelCreator->GoList)
	{
		moteur_->addGameObject(go);
	}
	
	for (Mesh* me : levelCreator->MeList)
	{
		moteur_->loadMesh(me);
	}
	
	for (Shader* sh : levelCreator->ShList)
	{
		moteur_->LoadShader(sh);
	}
	
	for (Collider* col : levelCreator->CoList)
	{
		moteur_->colliderManager()->addCollider(col);
	}
}

void InitGame::initGo()
{
	GameObject* player = new GameObject();

	Mesh* anchor = new Mesh("./Mesh/Cube.x");
	moteur_->loadMesh(anchor);
	
	Player* playerScript = new Player();
	
	player->addComponent(playerScript);
	player->addComponent(anchor);


	player->transform()->posZ(-1.f);
	moteur_->addGameObject(player);
	
	camera_->addComponent(playerScript);


	GameObject* levelManager = new GameObject();
	

	/*
	
	GameObject* PlayerGo = new GameObject();
	
	Mesh* chat = new Mesh("./Mesh/BONGUSV2.x");
	moteur_->loadMesh(chat);
	
	PlayerGo->addComponent(chat);
	PlayerGo->addComponent(player);

	PlayerGo->transform()->position(D3DXVECTOR3(0.f, 3.f, 0.f));
	PlayerGo->transform()->scale(D3DXVECTOR3(3.f, 3.f, 3.f));*/
	//moteur_->addGameObject(ca);

}


void InitGame::update()
{
	levelCreator->GenerateLevel();
}




