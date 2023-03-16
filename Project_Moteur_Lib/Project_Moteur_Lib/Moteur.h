#pragma once
#include <windows.h>
#include <windowsx.h>
#include <d3d9.h>
#include <d3dx9.h>

#include "Utils.h"

#include "Vertice.h"
#include "GameObject.h"

LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);


class Moteur
{

private:

    LPDIRECT3D9 d3d;    // the pointer to our Direct3D interface
    LPDIRECT3DDEVICE9 d3ddev;    // the pointer to the device class
    LPDIRECT3DINDEXBUFFER9 i_buffer = NULL;


    #define CUSTOMFVF (D3DFVF_XYZ | D3DFVF_NORMAL)

    //SCREEN size
    int SWidth;
    int SHeight;

    HWND hWnd;
    WNDCLASSEX wc;

    vector<GameObject*> gameObjectList;
    int goLisSize;


public:

    void init(HINSTANCE hInstance,
        HINSTANCE hPrevInstance,
        LPSTR lpCmdLine,
        int nCmdShow,
        int SCREEN_WIDTH,
        int SCREEN_HEIGHT);


    void initD3D(HWND hWnd);    // sets up and initializes Direct3D
    void render(void);    // renders a single frame
    void cleanD3D(void);    // closes Direct3D and releases memory
    void init_light(void);    // sets up the light and the material
    void setUpRenderCamera();
    void addGameObject(GameObject* GO);

    void addMeshToscene(Vertice* verti);
    LPDIRECT3DINDEXBUFFER9 createIndiceBuffer(short indices[] = NULL);



};