#ifdef _DEBUG
#include <crtdbg.h>
#endif

#include "Utils.h"


const int FIXED_UPDATE_INTERVAL = 16; // 16ms, equivalent to 60fps

#pragma region test area

void triggerHapened(Collider* other) { Utils::DebugLogMessage("Weeeeee"); }

#pragma endregion

void calltest() { Utils::DebugLogMessage("Reussi"); };

#pragma endregion

int main(Moteur* moteur)
{	

#pragma region Init

	Mesh* WallMesh = moteur->ImportingModel("./Mesh/cube.x");

	Shader* Red = moteur->LoadShader("./Shader/Red.hlsl");
	Red->name = "ROUGE";
	Shader* Green = moteur->LoadShader("./Shader/Green.hlsl");
	Shader* Blue = moteur->LoadShader("./Shader/Blue.hlsl");
	Shader* Yellow = moteur->LoadShader("./Shader/Yellow.hlsl");
	Yellow->name = "YELLOW";
	Shader* Pink = moteur->LoadShader("./Shader/Pink.hlsl");

	D3DXVECTOR3* position = new D3DXVECTOR3(0.f, 4.f, 0.f);
	D3DXVECTOR3* rotation = new D3DXVECTOR3(0.f, 0.f, 0.f);
	GameObject* Wall_ = CreateGameObject::Wall(*WallMesh, Red, position, rotation);

	D3DXVECTOR3* position2 = new D3DXVECTOR3(4.f, 0.f, 5.f);
	D3DXVECTOR3* rotation2 = new D3DXVECTOR3(0.f, -M_PI_2, 0.f);
	GameObject* Wall2_ = CreateGameObject::Wall(*WallMesh, Yellow, position2, rotation2);

	/*moteur->addGameObject(Wall_);
	moteur->addGameObject(Wall2_);*/

#pragma endregion


#pragma region GameInit

	
	moteur->camera()->transform()->posZ(20.0f);
	moteur->camera()->transform()->posY(-7.0f);

	


	Mesh* cylinderMesh;
	cylinderMesh = moteur->ImportingModel("./Mesh/cylinder2.x");

	Mesh* anchormesh;
	anchormesh = moteur->ImportingModel("./Mesh/cubeRose.x");

	Mesh* meshPlayer;
	meshPlayer = moteur->ImportingModel("./Mesh/BONGUSV2.x");

	GameObject* playerParentRoad = new GameObject();
	GameObject* playerParentRoll = new GameObject(playerParentRoad);
	GameObject* player = new GameObject(playerParentRoll);

	GameObject* a[10];
	for (int x = 0; x < 10; ++x) {
		//MoveForward* roadcomponent = new MoveForward();

		a[x] = new GameObject();
		//a[x]->addComponent(roadcomponent);
		a[x]->addComponent(cylinderMesh);

		a[x]->transform()->addRoll(M_PI * 0.5);		
		a[x]->transform()->position((D3DXVECTOR3(-0.5f, -0.f, -0.f)));
		a[x]->transform()->scale(D3DXVECTOR3(2.f, 2.f, 2.f));
		a[x]->transform()->scaleY(5);
		a[x]->transform()->posZ(x * 10);
		moteur->addGameObject(a[x]);
	}	


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
	/*GameObject* score = new GameObject();
	score->addComponent( new Text());
	moteur->addGameObject(score);*/
	
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


