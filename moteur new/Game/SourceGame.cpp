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

	



	/*D3DXVECTOR3* position = new D3DXVECTOR3(0.f, 4.f, 0.f);
	D3DXVECTOR3* rotation = new D3DXVECTOR3(0.f, 0.f, 0.f);
	GameObject* Wall_ = CreateGameObject::Wall(*WallMesh, Red, position, rotation);

	D3DXVECTOR3* position2 = new D3DXVECTOR3(4.f, 0.f, 5.f);
	D3DXVECTOR3* rotation2 = new D3DXVECTOR3(0.f, -M_PI_2, 0.f);
	GameObject* Wall2_ = CreateGameObject::Wall(*WallMesh, Yellow, position2, rotation2);

	moteur->addGameObject(Wall_);
	moteur->addGameObject(Wall2_);*/

#pragma endregion


#pragma region GameInit


	Mesh* CubeMesh = moteur->ImportingModel("./Mesh/cube.x");
	Mesh* Playermesh = moteur->ImportingModel("./Mesh/BONGUSV2.x");
	Mesh* CylinderMesh = moteur->ImportingModel("./Mesh/CylinderRail.x");

	Shader* Red = moteur->LoadShader("./Shader/Red.hlsl");
	Shader* Green = moteur->LoadShader("./Shader/Green.hlsl");
	Shader* Blue = moteur->LoadShader("./Shader/Blue.hlsl");
	Shader* Yellow = moteur->LoadShader("./Shader/Yellow.hlsl");
	Shader* Pink = moteur->LoadShader("./Shader/Pink.hlsl");



	moteur->camera()->transform()->posZ(20.0f);
	moteur->camera()->transform()->posY(-7.0f);

	moteur->camera()->transform()->addRollPitchYaw(0.0f, 0.f, 0.0f);


	//LevelGenerator* level = new LevelGenerator(moteur);

	//level->GenerateLevel();

	
	

	

	GameObject* a[10];
	for (int x = 0; x < 10; ++x) {
		//MoveForward* roadcomponent = new MoveForward();

		a[x] = new GameObject();
		//a[x]->addComponent(roadcomponent);
		a[x]->addComponent(CylinderMesh);

		a[x]->transform()->addRoll(M_PI * 0.5);		
		a[x]->transform()->position((D3DXVECTOR3(-0.5f, -0.f, -0.f)));
		a[x]->transform()->scale(D3DXVECTOR3(2.f, 2.f, 2.f));
		a[x]->transform()->scaleY(5);
		a[x]->transform()->posZ(x * 10);
		moteur->addGameObject(a[x]);
	}	

	
	

	GameObject* PlayerGo = new GameObject();
	
	Player* player_ = new Player();

	PlayerGo->addComponent(player_);
	PlayerGo->addComponent(Playermesh);

	PlayerGo->transform()->scale(D3DXVECTOR3(0.3f, 0.3f, 0.3f));

	RigidBody* rb = new RigidBody();



	moteur->addGameObject(PlayerGo);

	moteur->camera()->parent(PlayerGo);

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


