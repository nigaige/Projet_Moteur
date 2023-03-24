
#include <Utils.h>
#include <chrono>
#include <thread>
#include "GoTester.h"
#include "MoveForward.h"

#ifdef _DEBUG
#include <crtdbg.h>
#endif

const int FIXED_UPDATE_INTERVAL = 16; // 16ms, equivalent to 60fps




#pragma endregion

int main(Moteur* moteur)
{	
	moteur->camera()->transform()->posZ(20.0f);
	moteur->camera()->transform()->posY(-5.0f);

	Mesh* meshCube;
	meshCube = moteur->ImportingModel("./Mesh/BONGUSV2.x");
	Mesh* meshPlayer;
	meshPlayer = moteur->ImportingModel("./Mesh/test.x");

	GameObject* player = new GameObject;

	GameObject* a[10];
	for (int x = 0; x < 10; ++x) {
		
		MoveForward* roadcomponent = new MoveForward();

		a[x] = new GameObject();
		a[x]->addComponent(roadcomponent);
		a[x]->addComponent(meshCube);

		a[x]->addComponent(new GoTester());		
		a[x]->transform()->addRoll(M_PI*0.5);
		a[x]->transform()->scaleY(5);
		a[x]->transform()->posY(x * 10);
		moteur->addGameObject(a[x]);

	}


	moteur->gameLoop();

	delete moteur;

	//return msg.wParam;

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


