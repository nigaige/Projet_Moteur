

#ifdef _DEBUG
#include <crtdbg.h>
#endif

#include "Utils.h";


const int FIXED_UPDATE_INTERVAL = 16; // 16ms, equivalent to 60fps

#pragma region test area

void triggerHapened(Collider* other) { Utils::DebugLogMessage("Weeeeee"); }

#pragma endregion

void calltest() { Utils::DebugLogMessage("Reussi"); };

#pragma endregion

int main(Moteur* moteur)
{	

#pragma region Init
	
	
	moteur->camera()->transform()->posZ(20.0f);
	GameObject* kinematicCube = new GameObject();
	GameObject* nonKinematicCube = new GameObject();
	Mesh* m_cube = moteur->ImportingModel("./Mesh/Cube.x");
	Singe = new GameObject();
	//burbur = moteur->ImportingModel("./Mesh/Cube.x");

	std::string path = "C:/Users/Asabi/Documents/GitHub/Projet_Moteur_Lib/moteur new/Game/Shader/red.hlsl";
	std::string pathModel = "./Mesh/CUBEN.x";

	//burbur = moteur->LoadShader(&path);
	burbur = moteur->ImportingModel(pathModel);

	Shader* redShader = moteur->LoadShader(&path);

	//burbur->shader(redShader);

	kinematicCube->addComponent(m_cube);
	nonKinematicCube->addComponent(m_cube);

	kinematicCube->addComponent(new GoTester());

	RigidBody* rb = new RigidBody();
	rb->isKinematic(true);
	rb->hasGravity(false);
	kinematicCube->addComponent(rb);
	kinematicCube->transform()->posY(-5.0f);
	//kinematicCube->transform()->posX(-2.0f);

	nonKinematicCube->addComponent(new RigidBody());

	ColliderCube* sph1 = new ColliderCube(new D3DXVECTOR3(0, 0, 0), new D3DXVECTOR3(1, 1, 1));
	ColliderCube* sph2 = new ColliderCube(new D3DXVECTOR3(0, 0, 0), new D3DXVECTOR3(1, 1, 1));
	sph1->isTrigger(true);
	sph2->triggerCallback(triggerHapened);
	moteur->colliderManager()->addCollider(sph2);
	moteur->colliderManager()->addCollider(sph1);

	nonKinematicCube->addComponent(sph1);
	kinematicCube->addComponent(sph2);

	






	moteur->addGameObject(nonKinematicCube);
	moteur->addGameObject(kinematicCube);





#pragma endregion


#pragma region GameInit

	/*
	moteur->camera()->transform()->posZ(20.0f);
	moteur->camera()->transform()->posY(-5.0f);

	


	Mesh* meshCube;
	meshCube = moteur->ImportingModel("./Mesh/cylinder2.x");
	Mesh* anchormesh;
	anchormesh = moteur->ImportingModel("./Mesh/cubeRose.x");
	Mesh* meshPlayer;
	meshPlayer = moteur->ImportingModel("./Mesh/BONGUSV2.x");

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
		moteur->addGameObject(a[x]);
	}	
*/

	player->addComponent(meshPlayer);
	player->transform()->scale(D3DXVECTOR3(0.1f, 0.1f, 0.1f));

	playerParentRoad->addComponent(anchormesh);
	playerParentRoll->addComponent(new playerRolling);
	//playerParent->transform()->posY(4.f);
	playerParentRoll->transform()->posY(3.f);
	player->transform()->posY(-0.5f);
	player->addComponent(new playerRoll);
	playerParentRoad->addComponent(new playerRoll);
	moteur->camera()->addComponent(new playerRoll);

	//moteur->camera()->parent(playerParentRoad);


	moteur->addGameObject(playerParentRoad);
	moteur->addGameObject(playerParentRoll);
	moteur->addGameObject(player);
	GameObject* score = new GameObject();
	score->addComponent( new Text());
	moteur->addGameObject(score);

	enum Test
	{
		PHASE1,
		PHASE2
	};
	
	SM->setStates(PHASE2, listState);

	GameObject* SMGO = new GameObject;
	SMGO->addComponent(SM);
	moteur->addGameObject(SMGO);
	
	moteur->gameLoop();


#pragma region end game



#pragma endregion

	delete moteur;

	std::this_thread::sleep_for(std::chrono::milliseconds(1));

	return 0;
}


int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
#ifdef _DEBUG
	_CrtMemState memStateInit;
	_CrtMemCheckpoint(&memStateInit);
#endif

	Moteur* moteur;


	Utils util;
	util.DebugLogMessage("ok");

	moteur = new Moteur(hInstance,
		hPrevInstance,
		lpCmdLine,
		nCmdShow);
	moteur->Init();

	main(moteur);


#ifdef _DEBUG
	_CrtMemState memStateEnd, memStateDiff;
	_CrtMemCheckpoint(&memStateEnd);
	if (_CrtMemDifference(&memStateDiff, &memStateInit, &memStateEnd))
	{
		MessageBoxA(NULL, "MEMORY LEAKS", "DISCLAIMER", 0);
	}
#endif 

	return 0;
}


