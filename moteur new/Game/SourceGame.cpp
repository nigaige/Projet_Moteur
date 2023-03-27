
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
MSG msg;
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
	//burbur = moteur->ImportingModel("./Mesh/Cube.x");
	std::string path = "C:/Users/Asabi/Documents/GitHub/Projet_Moteur_Lib/moteur new/Game/Shader/red.hlsl";
	burbur = moteur->LoadShader(&path);

	Singe->addComponent(burbur);

	moteur->addGameObject(Singe);
	Singe->addComponent(new GoTester());

	





	//----------------------------FixedUpdate-----------------------------------//
	while (TRUE)
	{
		auto lastUpdateTime = std::chrono::high_resolution_clock::now();

		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}	
		moteur->update();
		moteur->render();

		if (msg.message == WM_QUIT)
			break;
		auto currentTime = std::chrono::high_resolution_clock::now();
		auto deltaTime = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - lastUpdateTime);
		if (deltaTime.count() >= FIXED_UPDATE_INTERVAL)
		{
			fixedUpdate();
			lastUpdateTime = currentTime;
		}
	}
	//----------------------------FixedUpdate-----------------------------------//


	delete moteur;

	return msg.wParam;

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

