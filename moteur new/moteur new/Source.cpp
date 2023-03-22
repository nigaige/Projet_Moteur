#include "Utils.h"
#pragma region testing
	
CUSTOMVERTEX points[] = {
	{ -1.0f, -1.0f, 1.0f, D3DCOLOR_XRGB(0, 0, 255), },//1
	{ 1.0f, -1.0f, 1.0f, D3DCOLOR_XRGB(0, 0, 255), },//2
	{ -1.0f, 1.0f, 1.0f, D3DCOLOR_XRGB(0, 0, 255), },//3
	{ 1.0f, 1.0f, 1.0f, D3DCOLOR_XRGB(0, 0, 255), },//4

	{ -1.0f, -1.0f, -1.0f, D3DCOLOR_XRGB(0, 0, 255), },//5
	{ 1.0f, -1.0f, -1.0f, D3DCOLOR_XRGB(0, 0, 255), },//6
	{ -1.0f, 1.0f, -1.0f, D3DCOLOR_XRGB(0, 0, 255), },//7
	{ 1.0f, 1.0f, -1.0f, D3DCOLOR_XRGB(0, 0, 255), },//8

};



/*
	CUSTOMVERTEX vertices[] =
	{
		{ 1.0f, -1.0f, 0.0f, D3DCOLOR_XRGB(0, 0, 255), },
		{ -1.0f, 1.0f, 0.0f, D3DCOLOR_XRGB(0, 255, 0), },
		{ -1.0f, -1.0f, 0.0f, D3DCOLOR_XRGB(255, 0, 0),},
		
		{ 1.0f, -1.0f, 0.0f, D3DCOLOR_XRGB(255, 0, 0),},
		{ 1.0f, 1.0f, 0.0f, D3DCOLOR_XRGB(0, 255, 0), },
		{ -1.0f, 1.0f, 0.0f, D3DCOLOR_XRGB(0, 0, 255), },
	};*/


CUSTOMVERTEX vertices[] =
{
		{ 1.0f, -1.0f, 0.0f, D3DCOLOR_XRGB(0, 0, 255), },
		{ -1.0f, 1.0f, 0.0f, D3DCOLOR_XRGB(0, 255, 0), },
		{ -1.0f, -1.0f, 0.0f, D3DCOLOR_XRGB(255, 0, 0),},
		





};


#include "GoTester.h"

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


	M->camera()->transform()->posZ(10.0f);
	

	GameObject* triangle = new GameObject();
	Mesh* forme = new Mesh(D3DPT_TRIANGLELIST);
	
	GameObject* GoImported = new GameObject();
	Mesh* MeshImported = M->ImportingModel("./Mesh/CUBEN.x");


	for (int i = 0; i < sizeof(vertices)/ sizeof(CUSTOMVERTEX); i++) {
		forme->addVertex(vertices + i);
	}
	forme->deduceTriangle();
	M->loadMeshInScene(forme);
	triangle->addComponent(forme);
	M->addGameObject(triangle);

	//triangle->addComponent(new GoTester(M->inputManager()));

	//M->camera()->addComponent(new GoTester(M->inputManager()));

	
	//M->camera()->transform()->addPitch(M_PI);


	GoImported->addComponent(MeshImported);
	GoImported->addComponent(new GoTester(M->inputManager()));
	M->addGameObject(GoImported);

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

		M->update();
		M->render();
	}

	// clean up DirectX and COM
	delete M;

	return msg.wParam;
}





