#pragma once
#include "Utils.h"

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

Moteur::~Moteur()
{
	Utils::DeleteVector(GOList);
	Utils::DeleteVector(MeList);
	cleanD3D();

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

	inputManager_ = new Input();
}

void Moteur::loadMeshInScene(Mesh* MeshToLoad) {
	LPDIRECT3DVERTEXBUFFER9 v_buffer = NULL;    // the pointer to the vertex buffer
	CUSTOMVERTEX* pVoid;    // a void pointer

	std::vector<CUSTOMVERTEX*> vList = *MeshToLoad->vertex();		//TODO OPTI POINTER?

	d3ddev->CreateVertexBuffer(vList.size() * sizeof(CUSTOMVERTEX),
		0,
		CUSTOMFVF,
		D3DPOOL_MANAGED,
		&v_buffer,
		NULL);
	
	v_buffer->Lock(0, 0, (void**)&pVoid, 0);
	
	for (int i = 0; i <	vList.size(); i++) {
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
	


	camera_ = new GameObject();
	cameraComponent = new Camera(45, 1.0f, 100.0f);
	camera_->addComponent(cameraComponent);
	

}

void Moteur::cleanD3D(void)
{
	d3ddev->Release();    // close and release the 3D device
	d3d->Release();    // close and release Direct3D
}

void Moteur::render(void)
{
	
	d3ddev->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);

	d3ddev->BeginScene();

	// SET UP THE PIPELINE
	setUpCamera();


	for (GameObject* go : GOList) {
		
		d3ddev->SetTransform(D3DTS_WORLD, go->transform()->displayValue());    // set the projection

		if (go->meshToDraw().size() == 0) continue;
		for (Mesh* m : go->meshToDraw()) {
			// select the vertex buffer to display
			d3ddev->SetStreamSource(0, m->Vbuffer(), 0, sizeof(CUSTOMVERTEX));

			// copy the vertex buffer to the back buffer
			d3ddev->DrawPrimitive(m->primitivMethode(), 0, m->Primitiv());
		}
	}
	d3ddev->EndScene();

	d3ddev->Present(NULL, NULL, NULL, NULL);
}

void Moteur::update(void)
{

	inputManager_->InputUpdate();
	camera_->update();
	for (GameObject* go : GOList) {
		go->update();
	}
}


void Moteur::setUpCamera() {//TODO Transform input

	// select which vertex format we are using

	d3ddev->SetFVF(CUSTOMFVF);

	//d3ddev->SetTransform(D3DTS_VIEW, cameraComponent->updateCamera());


	D3DXVECTOR3 pEye(0.0f, 0.0f, 20.0f);
	D3DXVECTOR3 pAt(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 pUp(0.0f, 1.0f, 0.0f);
	D3DXMATRIX matView;    // the view transform matrix

	D3DXMatrixLookAtLH(&matView,
		&pEye,    // the camera position
		&pAt,    // the look-at position
		&pUp);    // the up direction


	d3ddev->SetTransform(D3DTS_VIEW, cameraComponent->transform()->displayValue());


	D3DXMATRIX matProjection;     // the projection transform matrix

	D3DXMatrixPerspectiveFovLH(&matProjection,
		D3DXToRadian(cameraComponent->fov()),    // the horizontal field of view
		(FLOAT)SCREEN_WIDTH / (FLOAT)SCREEN_HEIGHT, // aspect ratio
		cameraComponent->nearViewPlane(),    // the near view-plane
		cameraComponent->farViewPlane());    // the far view-plane

	d3ddev->SetTransform(D3DTS_PROJECTION, &matProjection);    // set the projection
}

GameObject* Moteur::camera()
{
	return camera_;
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


void Moteur::addMesh(Mesh* me)
{
	MeList.push_back(me);

}

void Moteur::rmMesh(Mesh* me)
{
	delete me;
	for (int i = 0; i < MeList.size(); i++) {
		if (MeList[i] == me) {
			MeList.erase(MeList.begin() + i, MeList.begin() + i + 1);
			return;
		}
	}
}



Shader Moteur::LoadShader(std::string* shaderPath)
{
	ID3DXBuffer* listing_f = NULL;
	ID3DXBuffer* listing_v = NULL;
	ID3DXBuffer* code_f = NULL;
	ID3DXBuffer* code_v = NULL;
	LPD3DXCONSTANTTABLE* ppConstantTable_OUT = NULL;
	LPD3DXBUFFER shaderContent_ = NULL;
	IDirect3DVertexShader9** ppShader;

	std::ifstream file;

	file.open("C:/Users/asabi/Desktop/text.hlsl", std::ios_base::binary);
	//file.open(*shaderPath, std::ios_base::binary);

	if (file)
	{
		file.seekg(0, file.end);
		int length = file.tellg();
		file.seekg(0, file.beg);
		char* _Str = new char[length + 1];
		file.read(_Str, length);
		_Str[length] = 0;

		HRESULT Buffer = D3DXCompileShader((LPCSTR)_Str, strlen(_Str), NULL, NULL, "main_vertex", "vs_3_0", 0, &code_v, &listing_v, ppConstantTable_OUT);

		d3ddev->CreateVertexShader((DWORD*)Buffer, ppShader);

		d3ddev->SetVertexShader(*ppShader);

		return *new Shader(ppShader);
	}
}