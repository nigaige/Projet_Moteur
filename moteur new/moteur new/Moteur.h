#pragma once
#include "Utils.h"

class Moteur
{
private:

    LPDIRECT3D9 d3d;    // the pointer to our Direct3D interface
    LPDIRECT3DDEVICE9 d3ddev;    // the pointer to the device class
	LPDIRECT3DVERTEXBUFFER9 v_buffer = NULL;    // the pointer to the vertex buffer

	HWND hWnd;
	WNDCLASSEX wc;

	int nCmdShow;

	Mesh* triangle;


public:

    Moteur(HINSTANCE hInstance,
		HINSTANCE hPrevInstance,
		LPSTR lpCmdLine,
		int nCmdShow);

	void Init();
	void init_graphics(void);
	void initD3D();
	void cleanD3D(void);
	void render(void);
};

