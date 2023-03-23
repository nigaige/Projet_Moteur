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
{/*
		{ 1.0f, -1.0f, 0.0f, D3DCOLOR_XRGB(0, 0, 255), },
		{ -1.0f, 1.0f, 0.0f, D3DCOLOR_XRGB(0, 255, 0), },
		{ -1.0f, -1.0f, 0.0f, D3DCOLOR_XRGB(255, 0, 0),},
		*/

{ 1.000000f, 1.000000f, 1.000000f, D3DCOLOR_XRGB(0, 0, 255), },
{ -1.000000f, 1.000000f, 1.000000f, D3DCOLOR_XRGB(0, 0, 255), },
{ -1.000000f, 1.000000f, -1.000000f, D3DCOLOR_XRGB(0, 0, 255), },
{ 1.000000f, 1.000000f, -1.000000f, D3DCOLOR_XRGB(0, 0, 255), },
{ 1.000000f, -1.000000f, -1.000000f, D3DCOLOR_XRGB(0, 0, 255), },
{ 1.000000f, 1.000000f, -1.000000f, D3DCOLOR_XRGB(0, 0, 255), },
{ -1.000000f, 1.000000f, -1.000000f, D3DCOLOR_XRGB(0, 0, 255), },
{ -1.000000f, -1.000000f, -1.000000f, D3DCOLOR_XRGB(0, 0, 255), },
{ -1.000000f, -1.000000f, -1.000000f, D3DCOLOR_XRGB(0, 0, 255), },
{ -1.000000f, 1.000000f, -1.000000f, D3DCOLOR_XRGB(0, 0, 255), },
{ -1.000000f, 1.000000f, 1.000000f, D3DCOLOR_XRGB(0, 0, 255), },
{ -1.000000f, -1.000000f, 1.000000f, D3DCOLOR_XRGB(0, 0, 255), },
{ -1.000000f, -1.000000f, 1.000000f, D3DCOLOR_XRGB(0, 0, 255), },
{ 1.000000f, -1.000000f, 1.000000f, D3DCOLOR_XRGB(0, 0, 255), },
{ 1.000000f, -1.000000f, -1.000000f, D3DCOLOR_XRGB(0, 0, 255), },
{ -1.000000f, -1.000000f, -1.000000f, D3DCOLOR_XRGB(0, 0, 255), },
{ 1.000000f, -1.000000f, 1.000000f, D3DCOLOR_XRGB(0, 0, 255), },
{ 1.000000f, 1.000000f, 1.000000f, D3DCOLOR_XRGB(0, 0, 255), },
{ 1.000000f, 1.000000f, -1.000000f, D3DCOLOR_XRGB(0, 0, 255), },
{ 1.000000f, -1.000000f, -1.000000f, D3DCOLOR_XRGB(0, 0, 255), },
{ -1.000000f, -1.000000f, 1.000000f, D3DCOLOR_XRGB(0, 0, 255), },
{ -1.000000f, 1.000000f, 1.000000f, D3DCOLOR_XRGB(0, 0, 255), },
{ 1.000000f, 1.000000f, 1.000000f, D3DCOLOR_XRGB(0, 0, 255), },
{ 1.000000f, -1.000000f, 1.000000f, D3DCOLOR_XRGB(0, 0, 255), }



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



	GameObject* triangle = new GameObject();
	Mesh* forme = new Mesh(D3DPT_TRIANGLELIST);
	for (int i = 0; i < sizeof(vertices)/ sizeof(CUSTOMVERTEX); i++) {
		forme->addVertex(vertices + i);
	}

	M->camera()->transform()->posZ(20.0f);




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
	
	ColliderSphere* sph1 = new ColliderSphere(new D3DXVECTOR3(0, 0, 0), 1);
	ColliderSphere* sph2 = new ColliderSphere(new D3DXVECTOR3(0,0,0), 1);
	M->colliderManager()->addCollider(sph1);
	M->colliderManager()->addCollider(sph2);
	nonKinematicCube->addComponent(sph1);
	kinematicCube->addComponent(sph2);


	
	M->addGameObject(kinematicCube);
	M->addGameObject(nonKinematicCube);
	

	Moteur::s_deltaTime_ = 0.1f;


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





