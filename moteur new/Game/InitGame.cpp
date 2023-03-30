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
	moteur_->camera()->transform()->posZ(20.0f);
	moteur_->camera()->transform()->posY(-5.0f);
	
	Mesh* meshCube = moteur_->ImportingModel("./Mesh/CylinderRail.x");
	Mesh* anchormesh = moteur_->ImportingModel("./Mesh/cubeRose.x");
	Mesh* meshPlayer = moteur_->ImportingModel("./Mesh/BONGUSV2.x");

	GameObject* roadCenter = new GameObject();
	GameObject* rollCenter = new GameObject();
	GameObject* player = new GameObject();
	moteur_->addGameObject(roadCenter);
	moteur_->addGameObject(rollCenter);
	moteur_->addGameObject(player);

	player->addComponent(meshPlayer);

	player->transform()->scale(D3DXVECTOR3(0.1f, 0.1f, 0.1f));
	player->transform()->posY(-0.5f);
	player->parent(rollCenter);

	rollCenter->parent(roadCenter);
	rollCenter->transform()->posY(3.f);
	player->addComponent(new PlayerRolling());

	roadCenter->addComponent(new playerRoll);
	


	//ROAD

	/*GameObject* a[10];
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
	}*/

	

	Parser* testParsing = new Parser();
	testParsing->Filename("./ImportScript/ImportWall.txt");
	testParsing->ParseAll();

	std::vector<GameObject*> GOList = testParsing->GOlist();
	std::vector<Mesh*> MeList = testParsing->MElist();
	std::vector<Shader*> shList = testParsing->SHlist();
	std::vector<Collider*> CoList = testParsing->COlist();
	
	for (GameObject* go : GOList) {
		moteur_->addGameObject(go);
	}
	for (Mesh* me : MeList) {
		moteur_->loadMesh(me);
	}
	for (Shader* sh : shList) {
		moteur_->LoadShader(sh);
	}
	for (Collider* col : CoList)
	{
		moteur_->colliderManager()->addCollider(col);
	}

	

	/*
	Parser* testParsing = new Parser();
	testParsing->Filename("./ImportScript/FORMAIN.txt");
	testParsing->ParseAll();

	std::vector<GameObject*> GOList = testParsing->GOlist();
	std::vector<Mesh*> MeList = testParsing->MElist();
	std::vector<Shader*> shList = testParsing->SHlist();
	std::vector<Collider*> CoList = testParsing->COlist();
	
	for (GameObject* go : GOList) {
		moteur_->addGameObject(go);
	}
	for (Mesh* me : MeList) {
		moteur_->loadMesh(me);
	}
	for (Shader* sh : shList) {
		moteur_->LoadShader(sh);
	}
	for (Collider* col : CoList)
	{
		moteur_->colliderManager()->addCollider(col);
	}
	*/

}
