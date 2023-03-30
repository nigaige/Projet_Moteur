#include "Utils.h"
#include <tchar.h>
#include <chrono>


// this is the main message handler for the program
LRESULT CALLBACK WindowPro(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
	{
		PostQuitMessage(0);
		return 0;
		break;
	}
	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}

MemoryLeakFreeMoteur::MemoryLeakFreeMoteur(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{


	ZeroMemory(&wc, sizeof(WNDCLASSEX));

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WindowPro;
	wc.hInstance = hInstance;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.lpszClassName = L"WindowClass";

	RegisterClassEx(&wc);

	hWnd = CreateWindowEx(NULL, L"WindowClass", L"Our Direct3D Program",
		WS_OVERLAPPEDWINDOW, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT,
		NULL, NULL, hInstance, NULL);

	ShowWindow(hWnd, nCmdShow);


	d3d = Direct3DCreate9(D3D_SDK_VERSION);

	D3DPRESENT_PARAMETERS d3dpp;

	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.hDeviceWindow = hWnd;
	d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
	d3dpp.BackBufferWidth = SCREEN_WIDTH;
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;
	d3dpp.EnableAutoDepthStencil = TRUE;

	// create a device class using this information and the info from the d3dpp stuct
	d3d->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_PUREDEVICE,
		&d3dpp,
		&d3ddev);

	d3ddev->SetRenderState(D3DRS_LIGHTING, TRUE);
	d3ddev->SetRenderState(D3DRS_ZENABLE, TRUE);
	d3ddev->SetRenderState(D3DRS_AMBIENT, 0xffffffff);


}

MemoryLeakFreeMoteur::~MemoryLeakFreeMoteur()
{
	d3ddev->Release();    // close and release the 3D device
	d3d->Release();    // close and release Direct3D
	
	DestroyWindow(hWnd);
	UnregisterClass(L"WindowClass", wc.hInstance);

	Utils::DeleteVector(GOList);
	Utils::DeleteVector(MeList);
	delete colliderManager_;
	delete camera_;
	delete cameraComponent;
	delete initText;

}

void MemoryLeakFreeMoteur::loop()
{
	MSG msg = { 0 };

	//camera_ = new GameObject();
	//cameraComponent = new Camera(45, 1.0f, 100.0f);
	//camera_->addComponent(cameraComponent);

	while (WM_QUIT != msg.message)

	{

		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))

		{

			TranslateMessage(&msg);

			DispatchMessage(&msg);

		}

		else

		{


		}

	}
}
