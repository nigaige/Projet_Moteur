#include "Utils.h";


void InitGame::init(Moteur* moteur)
{
	
		std::vector<GameObject*> goList; 
	std::vector<Mesh*> meList;
	std::vector<Collider*> coList;
	std::vector<Shader*> shList;

	moteur->camera()->transform()->posZ(-15.0f);
	moteur->camera()->transform()->posY(3.0f);
	Parser* testParsing = new Parser();

	//Player Setup
	testParsing->Filename("./Map/Player.txt");
	try
	{
		testParsing->ParseAll(&goList, &meList, &coList, &shList);

	}
	catch (const std::exception& err)
	{
		Utils::DebugLogMessage(err.what());
		std::exit(EXIT_FAILURE);
	}
	
	MoveForward* PlayerMovement = new MoveForward();
	playerRoll* PlayerMovementRoll = new playerRoll();
	movingmap* MAPTEST = new movingmap(goList[0]);
	movingmap* MAPTEST2 = new movingmap(goList[0]);
	goList[0]->addComponent(PlayerMovement);
	goList[1]->addComponent(PlayerMovementRoll);
	goList[0]->parent(goList[1]);
	moteur->camera()->parent(goList[0]);
	goList[3]->parent(goList[4]);
	goList[2]->addComponent(MAPTEST);
	goList[4]->addComponent(MAPTEST2);

	for (Shader* sh : shList) {
		moteur->addShader(sh);
		moteur->LoadShader(sh);
	}


	for (GameObject* go : goList) {
		moteur->addGameObject(go);

	}


	for (Mesh* me : meList) {
		moteur->loadMesh(me);
	}

	
	for (Collider* col : coList)
	{
		moteur->colliderManager()->addCollider(col);
	}
	

	delete testParsing;

}
