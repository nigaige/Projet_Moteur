#include "Moteur.h"


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

Moteur::Moteur(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	this->nCmdShow = nCmdShow;


	ZeroMemory(&wc, sizeof(WNDCLASSEX));

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hInstance;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.lpszClassName = L"WindowClass";

	RegisterClassEx(&wc);

	hWnd = CreateWindowEx(NULL, L"WindowClass", L"Our Direct3D Program",
		WS_OVERLAPPEDWINDOW, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT,
		NULL, NULL, hInstance, NULL);

}

void Moteur::Init()
{

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

	// create a device class using this information and the info from the d3dpp stuct
	d3d->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp,
		&d3ddev);

	d3ddev->SetRenderState(D3DRS_LIGHTING, FALSE);    // turn off the 3D lighting


	initD3D();
}

void Moteur::loadMeshInScene(Mesh* MeshToLoad) {
	LPDIRECT3DVERTEXBUFFER9 v_buffer = NULL;    // the pointer to the vertex buffer
	CUSTOMVERTEX* pVoid;    // a void pointer

	d3ddev->CreateVertexBuffer(3 * sizeof(CUSTOMVERTEX),
		0,
		CUSTOMFVF,
		D3DPOOL_MANAGED,
		&v_buffer,
		NULL);
	
	v_buffer->Lock(0, 0, (void**)&pVoid, 0);
	
	std::vector<CUSTOMVERTEX*> vList = *MeshToLoad->vertex();		//TODO OPTI POINTER?
	for (int i = 0; i < 3; i++) {
		memcpy(pVoid + i, vList[i], sizeof(CUSTOMVERTEX));
	}

	v_buffer->Unlock();

	MeshToLoad->Vbuffer(v_buffer);
}


void Moteur::initD3D()
{
	d3d = Direct3DCreate9(D3D_SDK_VERSION);

	D3DPRESENT_PARAMETERS d3dpp;

	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.hDeviceWindow = hWnd;
	d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
	d3dpp.BackBufferWidth = SCREEN_WIDTH;
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;

	// create a device class using this information and the info from the d3dpp stuct
	d3d->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp,
		&d3ddev);

	d3ddev->SetRenderState(D3DRS_LIGHTING, FALSE);    // turn off the 3D lighting
}


void Moteur::render(void)
{

	d3ddev->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);

	d3ddev->BeginScene();

	// SET UP THE PIPELINE
	setUpCamera();

	for (GameObject* go : GOList) {
		d3ddev->SetTransform(D3DTS_WORLD, go->transform()->displayValue());    // set the projection

		//TODO transform
		for (Mesh* m : go->meshToDraw()) {
			// select the vertex buffer to display
			d3ddev->SetStreamSource(0, m->Vbuffer(), 0, sizeof(CUSTOMVERTEX));

			// copy the vertex buffer to the back buffer
			d3ddev->DrawPrimitive(m->primitivMethode(), 0, 1);

		}

	}
	d3ddev->EndScene();

	d3ddev->Present(NULL, NULL, NULL, NULL);
}


void Moteur::setUpCamera() {//TODO Transform input

	// select which vertex format we are using
	d3ddev->SetFVF(CUSTOMFVF);

	D3DXVECTOR3 pEye(0.0f, 0.0f, 10.0f);
	D3DXVECTOR3 pAt(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 pUp(0.0f, 1.0f, 0.0f);

	D3DXMATRIX matView;    // the view transform matrix

	D3DXMatrixLookAtLH(&matView,
		&pEye,    // the camera position
		&pAt,    // the look-at position
		&pUp);    // the up direction
	d3ddev->SetTransform(D3DTS_VIEW, &matView);

	D3DXMATRIX matProjection;     // the projection transform matrix

	D3DXMatrixPerspectiveFovLH(&matProjection,
		D3DXToRadian(45),    // the horizontal field of view
		(FLOAT)SCREEN_WIDTH / (FLOAT)SCREEN_HEIGHT, // aspect ratio
		1.0f,    // the near view-plane
		100.0f);    // the far view-plane

	d3ddev->SetTransform(D3DTS_PROJECTION, &matProjection);    // set the projection

}

void Moteur::addGameObject(GameObject* go)
{
	GOList.push_back(go);
}

void Moteur::rmGamObject(GameObject* go)
{
	delete go;
	for (int i = 0; i < GOList.size(); i++) {
		if (GOList[i] == go) {
			GOList.erase(GOList.begin() + i, GOList.begin() + i + 1);
			return;
		}
	}

}

void Moteur::cleanD3D(void)
{
	d3ddev->Release();    // close and release the 3D device
	d3d->Release();    // close and release Direct3D
}