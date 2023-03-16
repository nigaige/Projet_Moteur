// include the basic windows header files and the Direct3D header file

#pragma region Include and define
    #include <windows.h>
    #include <windowsx.h>
    #include <d3d9.h>
    #include <d3dx9.h>

    #include "Utils.h"
    #include "Moteur.h"

    #include "GameObject.h"
    #include "Vertice.h"

    // define the screen resolution
    #define SCREEN_WIDTH 600
    #define SCREEN_HEIGHT 800

    // include the Direct3D Library files
    #pragma comment (lib, "d3d9.lib")
    #pragma comment (lib, "d3dx9.lib")


    LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);


#pragma endregion


    CUSTOMVERTEX triangleMesh[] =
    {
        { -2.5f, -3.0f, 0.0f, D3DCOLOR_XRGB(255, 0, 0), },
        { 0.0f, 3.0f, 0.0f, D3DCOLOR_XRGB(0, 255, 0), },
        { 2.5f, -3.0f, 0.0f, D3DCOLOR_XRGB(0, 0, 255), },
    };



// the entry point for any Windows program
int WINAPI WinMain(HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPSTR lpCmdLine,
    int nCmdShow)
{




    Moteur* M = new Moteur();
    M->init(hInstance,
        hPrevInstance,
        lpCmdLine,
        nCmdShow,
        SCREEN_HEIGHT,
        SCREEN_WIDTH);

   

    //INIT SCENE
    GameObject* triangle = new GameObject(new Transform());
    Vertice* triangleVertice = new Vertice(triangleMesh,3, D3DPT_TRIANGLELIST);
    M->addMeshToscene(triangleVertice);
    triangle->addComponent(triangleVertice);
    triangle->toDisplay(true);
    M->addGameObject(triangle);

    // enter the main loop:

    MSG msg;

    while (TRUE)
    {
        while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        if (msg.message == WM_QUIT)
            break;

        M->render();
    }

    // clean up DirectX and COM
    M->cleanD3D();

    //TODO Clean gameobject
    return msg.wParam;
}


// this is the main message handler for the program
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_DESTROY:
    {
        PostQuitMessage(0);
        return 0;
    } break;
    }

    return DefWindowProc(hWnd, message, wParam, lParam);
}



