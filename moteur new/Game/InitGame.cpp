#include "Utils.h";


void InitGame::init(Moteur* moteur)
{
	moteur->camera()->transform()->posZ(20.0f);
	moteur->camera()->transform()->posY(-5.0f);
	
	Parser* testParsing = new Parser();
	testParsing->Filename("ImportWall.txt");
	

	MoveForward* PlayerMovement = new MoveForward();
	//playerRoll* PlayerMovementRoll = new playerRoll();
	//playerRoll* CamRoll = new playerRoll();
	//moteur->camera()->addComponent(PlayerMovement);
	std::vector<GameObject*> goList; 
	std::vector<Mesh*> meList;
	std::vector<Collider*> coList;
	std::vector<Shader*> shList;

	try
	{
		testParsing->ParseAll(&goList, &meList, &coList, &shList);

	}
	catch (const std::exception& err)
	{
		Utils::DebugLogMessage(err.what());
		std::exit(EXIT_FAILURE);
	}
	//moteur->camera()->parent();
	goList[0]->addComponent(PlayerMovement);
	//moteur->camera()->parent(goList[0]);
	//goList[1]->parent(goList[0]);

	for (Shader* sh : shList) {
		moteur->addShader(sh);
		moteur->LoadShader(sh);
	}


	for (GameObject* go : goList) {
		
		//go->addComponent(PlayerMovement);
		//go->addComponent(PlayerMovementRoll);
		//go->parent(moteur->camera());
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
