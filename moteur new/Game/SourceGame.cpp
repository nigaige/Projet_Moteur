
#include <Utils.h>
#include <chrono>
#include <thread>
#include "GoTester.h"
std::string* message;

#ifdef _DEBUG
#include <crtdbg.h>
#endif

const int FIXED_UPDATE_INTERVAL = 1006; // 16ms, equivalent to 60fps



void fixedUpdate()
{
	Utils util;
	util.DebugLogMessage("ok");

// Perform physics calculations and other time-sensitive operations here
}

int main(Moteur* M)
{

	MSG msg;
	GameObject* Singe;
	Mesh* burbur;


	M->camera()->transform()->posZ(20.0f);
	Singe = new GameObject();

	GameObject* kinematicCube = new GameObject();
	GameObject* nonKinematicCube = new GameObject();
	Mesh* m_cube = M->ImportingModel("./Mesh/Cube.x");

	kinematicCube->addComponent(m_cube);
	nonKinematicCube->addComponent(m_cube);

	kinematicCube->addComponent(new GoTester());

	RigidBody* rb = new RigidBody();
	rb->isKinematic(true);
	kinematicCube->addComponent(rb);
	kinematicCube->transform()->posY(-5.0f);

	nonKinematicCube->addComponent(new RigidBody());

	ColliderCube* sph1 = new ColliderCube(new D3DXVECTOR3(0, 0, 0), new D3DXVECTOR3(1, 1, 1));
	ColliderCube* sph2 = new ColliderCube(new D3DXVECTOR3(0, 0, 0), new D3DXVECTOR3(1, 1, 1));
	M->colliderManager()->addCollider(sph1);
	M->colliderManager()->addCollider(sph2);
	nonKinematicCube->addComponent(sph1);
	kinematicCube->addComponent(sph2);



	M->addGameObject(kinematicCube);
	M->addGameObject(nonKinematicCube);

	//----------------------------FixedUpdate-----------------------------------//
	while (TRUE)
	{
		auto lastUpdateTime = std::chrono::high_resolution_clock::now();

		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}	
		M->update();
		M->render();

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


	delete M;

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
	Moteur* M;

	M = new Moteur(hInstance,
		hPrevInstance,
		lpCmdLine,
		nCmdShow);
	M->Init();

	main(M);



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

