#pragma once
#include "Utils.h"

class Moteur
{
private:

    LPDIRECT3D9 d3d;    // the pointer to our Direct3D interface
    LPDIRECT3DDEVICE9 d3ddev;    // the pointer to the device class

	HWND hWnd;
	WNDCLASSEX wc;

	int nCmdShow;

	//Mesh* triangle;
	std::vector<GameObject*> GOList;

public:

    Moteur(HINSTANCE hInstance,
		HINSTANCE hPrevInstance,
		LPSTR lpCmdLine,
		int nCmdShow);

	void Init();
	void loadMeshInScene(Mesh* MeshToLoad);
	void initD3D();
	void cleanD3D(void);
	void render(void);

	void setUpCamera();

	void addGameObject(GameObject* go);
	void rmGamObject(GameObject* go);
};

