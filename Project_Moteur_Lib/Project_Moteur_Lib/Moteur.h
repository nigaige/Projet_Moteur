#pragma once
#include <windows.h>
#include <windowsx.h>
#include <d3d9.h>
#include <d3dx9.h>

#include "GameObject.h"
#include "Vertice.h"

LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);


class Moteur
{
private:

    LPDIRECT3D9 d3d;    // the pointer to our Direct3D interface
    LPDIRECT3DDEVICE9 d3ddev;    // the pointer to the device class
    LPDIRECT3DVERTEXBUFFER9 v_buffer = NULL;    // the pointer to the vertex buffer
    LPDIRECT3DINDEXBUFFER9 i_buffer = NULL;

    struct CUSTOMVERTEX { FLOAT X, Y, Z; D3DVECTOR NORMAL; };

    #define CUSTOMFVF (D3DFVF_XYZ | D3DFVF_NORMAL)

    //SCREEN size
    int SWidth;
    int SHeight;

    HWND hWnd;
    WNDCLASSEX wc;




public:

    void init(HINSTANCE hInstance,
        HINSTANCE hPrevInstance,
        LPSTR lpCmdLine,
        int nCmdShow,
        int SCREEN_WIDTH,
        int SCREEN_HEIGHT);


    void initD3D(HWND hWnd);    // sets up and initializes Direct3D
    void render(vector<GameObject*> gameObjectList, int size);    // renders a single frame
    void cleanD3D(void);    // closes Direct3D and releases memory
    void init_light(void);    // sets up the light and the material
    void setUpRenderCamera();

    void addMeshToscene(Vertice verti);



};

