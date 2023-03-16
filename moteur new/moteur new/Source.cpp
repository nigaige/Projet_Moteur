// include the basic windows header files and the Direct3D header file
#include "Utils.h"



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





