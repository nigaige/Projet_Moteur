// include the basic windows header files and the Direct3D header file
#include "Utils.h"

#pragma region testing


	CUSTOMVERTEX vertices[] =
	{
		{ 3.0f, -3.0f, 0.0f, D3DCOLOR_XRGB(0, 0, 255), },
		{ 0.0f, 3.0f, 0.0f, D3DCOLOR_XRGB(0, 255, 0), },
		{ -3.0f, -3.0f, 0.0f, D3DCOLOR_XRGB(255, 0, 0), },
	};

#pragma endregion






// the entry point for any Windows program
int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{

	Moteur* M = new Moteur(hInstance,
		hPrevInstance,
		lpCmdLine,
		nCmdShow);

	M->Init();

	GameObject* triangle = new GameObject();
	Mesh* forme = new Mesh(D3DPT_TRIANGLELIST);
	for (int i = 0; i < 3; i++) {
		forme->addVertex(vertices + i);
	}
	M->loadMeshInScene(forme);
	triangle->addComponent(forme);
	M->addGameObject(triangle);


	// set up and initialize Direct3D

	// enter the main loop:

	MSG msg;

	while (TRUE)
	{
		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		if (msg.message  == WM_QUIT)
			break;

		M->render();
	}

	// clean up DirectX and COM
	M->cleanD3D();

	return msg.wParam;
}





