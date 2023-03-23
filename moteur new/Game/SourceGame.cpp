
#include <Utils.h>
#include <chrono>
#include <thread>
#include "GoTester.h"
std::string* message;

#ifdef _DEBUG
#include <crtdbg.h>
#endif

const int FIXED_UPDATE_INTERVAL = 1006; // 16ms, equivalent to 60fps
Moteur* moteur;
GameObject* Singe;
Mesh* burbur;


void fixedUpdate()
{
	Utils util;
	util.DebugLogMessage("ok");

// Perform physics calculations and other time-sensitive operations here
}

int main()
{
	moteur->camera()->transform()->posZ(20.0f);
	Singe = new GameObject();
	burbur = moteur->ImportingModel("./Mesh/Cube.x");

	Singe->addComponent(burbur);

	moteur->addGameObject(Singe);
	Singe->addComponent(new GoTester());


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

	moteur = new Moteur(hInstance,
		hPrevInstance,
		lpCmdLine,
		nCmdShow);
	moteur->Init();

	main();



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


#pragma endregion

