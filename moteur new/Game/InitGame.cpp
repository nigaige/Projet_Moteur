#include "Utils.h";

InitGame::InitGame(Moteur* moteur)
{
	moteur_ = moteur;
	camera_ = moteur_->camera();
}

void InitGame::initLevel()
{
	LevelDesigner* levelCreator = new LevelDesigner();
	levelCreator->CreateSection("./ImportScript/ImportWall.txt");
	
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
	Player* player = new Player();

	camera_->addComponent(player);

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


void InitGame::init()
{
	camera_->transform()->posZ(25.0f);
	camera_->transform()->posY(-10.0f);
	
	camera_->transform()->addRoll(-0.2);

	initLevel();
	initGo();

}

void InitGame::update()
{
}




