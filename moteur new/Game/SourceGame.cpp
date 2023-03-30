

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






#pragma endregion


#pragma region GameInit

	moteur->camera()->transform()->posZ(20.0f);
	moteur->camera()->transform()->posY(-5.0f);


	GameObject* Ui = new GameObject();
	buttonLaunchGame* buttonStart = new buttonLaunchGame(moteur);
	Ui->addComponent(buttonStart);
	moteur->addGameObject(Ui);
	moteur->addUiComponent(buttonStart);


	
	Mesh* meshCube  = moteur->ImportingModel("./Mesh/cylinder2.x");
	Mesh* anchormesh = moteur->ImportingModel("./Mesh/cubeRose.x");
	Mesh* meshPlayer = moteur->ImportingModel("./Mesh/BONGUSV2.x");




	GameObject* roadCenter = new GameObject();
	GameObject* rollCenter = new GameObject();
	GameObject* player = new GameObject();
	moteur->addGameObject(roadCenter);
	moteur->addGameObject(rollCenter);
	moteur->addGameObject(player);

	player->addComponent(meshPlayer);
	
	player->transform()->scale(D3DXVECTOR3(0.1f, 0.1f, 0.1f));
	player->transform()->posY(-0.5f);
	player->parent(rollCenter);

	rollCenter->parent(roadCenter);
	rollCenter->transform()->posY(3.f);
	player->addComponent(new playerRolling());

	roadCenter->addComponent(new playerRoll);



	//ROAD

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

/*		*/
#pragma endregion

	


	moteur->gameLoop();




#pragma region end game



	std::this_thread::sleep_for(std::chrono::milliseconds(1));

	return 0;
#pragma endregion


}



float Moteur::s_deltaTime_;
ID3DXFont* Moteur::font;

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
#ifdef _DEBUG
	_CrtMemState memStateInit;
	_CrtMemCheckpoint(&memStateInit);
#endif
	
	
	Moteur::inputManager_ = new Input();
	Moteur::s_deltaTime_ = 0.01f;
	Moteur::font = nullptr;

	Moteur* moteur;


	Utils util;
	

	moteur = new Moteur(hInstance,
		hPrevInstance,
		lpCmdLine,
		nCmdShow);
	moteur->Init();

	main(moteur);
		
	delete moteur;

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


