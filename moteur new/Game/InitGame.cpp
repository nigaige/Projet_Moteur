#include "Utils.h";


void InitGame::init(Moteur* moteur)
{
	moteur->camera()->transform()->posZ(20.0f);
	moteur->camera()->transform()->posY(-5.0f);

	Parser* testParsing = new Parser();
	testParsing->Filename("ImportWall.txt");

	

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

	/*
	for (Collider* col : coList)
	{
		moteur->colliderManager()->addCollider(col);
	}
	*/
	for (Collider* col : coList) delete col;


	delete testParsing;

}
