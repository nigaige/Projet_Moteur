#include "Utils.h"
#include <tchar.h>
#include <chrono>


const int FIXED_UPDATE_INTERVAL = 16; // 16ms, equivalent to 60fps

Input* Moteur::inputManager_;

// this is the main message handler for the program
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
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

Moteur::Moteur(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPWSTR lpCmdLine,
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
	for (GameObject* go : GOList)  delete go;
	for (Mesh* me : MeList)delete me;

	//for (Mesh* me : MeList)DeleteVector<Mesh*>();
	//MeList.erase();

	delete camera_;
	cameraComponent = nullptr; //delete is handle by above line
	delete colliderManager_;
	delete initText;
	delete inputManager_;

	if (font) { font->Release(); font = 0; }


	cleanD3D();
	DestroyWindow(hWnd);
	UnregisterClass(L"WindowClass", wc.hInstance);



}

void Moteur::cleanD3D(void)
{
	d3ddev->Release();    // close and release the 3D device
	d3d->Release();    // close and release Direct3D
}

void Moteur::Init()
{

	ShowWindow(hWnd, nCmdShow);

	initD3D();

	camera_ = new GameObject();
	cameraComponent = new Camera(45, 1.0f, 100.0f);
	camera_->addComponent(cameraComponent);

	colliderManager_ = new ColliderManager();

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


void Moteur::gameLoop()
{
	auto lastUpdateTime = std::chrono::high_resolution_clock::now();

	MSG msg = { 0 };

	while (WM_QUIT != msg.message)
	{
		lastUpdateTime = std::chrono::high_resolution_clock::now();



		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			//TIME
			auto currentTime = std::chrono::high_resolution_clock::now();
			auto deltaTime = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - lastUpdateTime);
			s_deltaTime_ = deltaTime.count();

			//UPDATE
			update();
			//DO FIXED UPDATE?
			if (s_deltaTime_ >= FIXED_UPDATE_INTERVAL)
			{
				fixedUpdate();
				lastUpdateTime = currentTime;
			}
			//UPDATE TRANSFORM
			updateTransform();
			//RENDER
			render();
		}
	}
}

void Moteur::renderMaterial(Mesh* mesh)
{
	for (DWORD i = 0; i < mesh->matCount(); i++)
	{
		d3ddev->SetMaterial(&mesh->meshMaterials()[i]);
		if (mesh->meshTexture() != NULL)
		{
			if (mesh->shader() == NULL)
				d3ddev->SetTexture(0, mesh->meshTexture()[i]);
			else
				mesh->shader()->shaderBuffer()->SetTexture(0, mesh->meshTexture()[i]);
		}
		mesh->importedMesh()->DrawSubset(i);
	}
}

void Moteur::render(void)
{
	
	d3ddev->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
	d3ddev->Clear(0, NULL, D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);


	d3ddev->BeginScene();

	// SET UP THE PIPELINE
	setUpCamera();

	for (GameObject* go : GOList) {
		
		if (go->meshToDraw().size() == 0) continue;
		d3ddev->SetTransform(D3DTS_WORLD, go->transform()->worldValue());    // set the projection

		for (Mesh* mesh : go->meshToDraw()) {

			if (mesh->importedMesh() == NULL)
			{
				d3ddev->SetTransform(D3DTS_WORLD, go->transform()->displayValue());    // set the projection
				d3ddev->SetStreamSource(0, mesh->Vbuffer(), 0, sizeof(CUSTOMVERTEX));
				d3ddev->DrawPrimitive(mesh->primitivMethode(), 0, mesh->Primitiv());
			}else
			{
				if (mesh->shader() != NULL)
				{
					D3DXMATRIX matWPV = *go->transform()->displayValue();  //TODO worldMat
					matWPV *= *cameraComponent->matView();
					matWPV *= *cameraComponent->matProj();


					UINT passCount;
					mesh->shader()->shaderBuffer()->Begin(&passCount, NULL);

					for (int ipass = 0; ipass < passCount; ipass++)
					{
						mesh->shader()->shaderBuffer()->BeginPass(ipass); // Sélectionner la première passe de la technique

						mesh->shader()->SetMatrix(&matWPV);
						mesh->shader()->shaderBuffer()->CommitChanges();

						renderMaterial(mesh);

						mesh->shader()->shaderBuffer()->EndPass();
					}

					mesh->shader()->shaderBuffer()->End();
				}
				else 
				{
					renderMaterial(mesh);
				}
			}
		}

		
	}

	
	d3ddev->EndScene();

	d3ddev->Present(NULL, NULL, NULL, NULL);
}

void Moteur::update(void)
{

	Moteur::inputManager_->InputUpdate();
	camera_->update();
	for (GameObject* go : GOList) {
		go->update();
	}
	colliderManager_->manageCollision();
}

void Moteur::fixedUpdate(void)
{
	for (GameObject* go : GOList) {
		go->fixedUpdate();

	}
}

void Moteur::updateTransform(void)
{
	camera_->updateTransform();
	for (GameObject* go : GOList) {
		go->updateTransform();
	}
}


void Moteur::setUpCamera() {

	// select which vertex format we are using

	d3ddev->SetFVF(CUSTOMFVF);

	//d3ddev->SetTransform(D3DTS_VIEW, cameraComponent->updateCamera());

	D3DXMATRIX* matView = cameraComponent->gameObject()->worldMatrix();
	//D3DXMATRIX matView = *cameraComponent->transform()->displayValue();



	d3ddev->SetTransform(D3DTS_VIEW, matView );
	cameraComponent->matView(matView);

	D3DXMATRIX matProjection;     // the projection transform matrix

	D3DXMatrixPerspectiveFovLH(&matProjection,
		D3DXToRadian(cameraComponent->fov()),    // the horizontal field of view
		(FLOAT)SCREEN_WIDTH / (FLOAT)SCREEN_HEIGHT, // aspect ratio
		cameraComponent->nearViewPlane(),    // the near view-plane
		cameraComponent->farViewPlane());    // the far view-plane

	cameraComponent->matView(&matProjection);
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
	for (int i = 0; i < GOList.size(); i++) {
		if (GOList[i] == go) {
			GOList.erase(GOList.begin() + i, GOList.begin() + i + 1);
			return;
		}
	}
	delete go;
}


void Moteur::addMesh(Mesh* me)
{
	MeList.push_back(me);
}

void Moteur::rmMesh(Mesh* me)
{
	for (int i = 0; i < MeList.size(); i++) {
		if (MeList[i] == me) {
			MeList.erase(MeList.begin() + i, MeList.begin() + i + 1);
			return;
		}
	}
	delete me;
}


/// <summary>
/// Return a pointeur of Shader by .hlsl pathfile
/// </summary>
/// <param name="shaderPath">String shaderPath of .hlsl file</param>
/// <returns>Shader* new Shader()</returns>
Shader* Moteur::LoadShader(std::string* shaderPath)
{
	LPD3DXEFFECT shaderBuff;
	D3DXHANDLE m_hT;
	D3DXHANDLE m_hMat;
	ID3DXBuffer* errors = NULL;
	
	HRESULT hr = D3DXCreateEffectFromFileA(
	d3ddev, // Pointeur vers l'interface du périphérique Direct3D
	shaderPath->c_str(), // Nom du fichier HLSL
	NULL, // Tableau des macros de préprocesseur (optionnel)
	NULL, // Interface de rappel pour les messages (optionnel)
	D3DXSHADER_PACKMATRIX_COLUMNMAJOR | D3DXSHADER_DEBUG, // Options de compilation
	NULL, // Interface de gestion de compilation (optionnel)
	&shaderBuff, // Pointeur vers l'effet créé
	&errors // Pointeur vers le buffer d'erreur (optionnel)
	);

	if(hr == D3D_OK)
	{
		m_hT = shaderBuff->GetTechniqueByName("Default");
		m_hMat = shaderBuff->GetParameterByName(m_hT, "worldViewProj");
		int a = 0;
	}

	return new Shader(shaderBuff);
}

/// <summary>
/// Return a pointeur of a Mesh by .x filepath
/// </summary>
/// <param name="path">String path of .x file</param>
/// <returns>Mesh* resultMesh</returns>
Mesh* Moteur::ImportingModel(std::string path)
{
	
	LPD3DXBUFFER materialBuffer = NULL;
	DWORD numMaterial = 0;
	LPD3DXMESH mesh = nullptr;
	


	Mesh* resultMesh = new Mesh(D3DPT_TRIANGLELIST);
	

	HRESULT hr = D3DXLoadMeshFromXA(path.c_str(), D3DXMESH_MANAGED, d3ddev, NULL, &materialBuffer, NULL, &numMaterial, &mesh); //Import mesh in meshImp
	if (FAILED(hr))
		Utils::DebugLogMessage("Failed import model");


	resultMesh->importedMesh(mesh);
	resultMesh->materialBuffer(materialBuffer);
	resultMesh->matCount(numMaterial);


	D3DXMATERIAL* materials = (D3DXMATERIAL*)resultMesh->materialBuffer()->GetBufferPointer();

	resultMesh->meshMaterials(new D3DMATERIAL9[resultMesh->matCount()]);
	resultMesh->meshTexture(new LPDIRECT3DTEXTURE9[resultMesh->matCount()]);

	if (resultMesh->meshMaterials() != NULL)
	{
		for (DWORD i = 0; i < resultMesh->matCount(); i++)
		{
			resultMesh->meshMaterials()[i] = materials[i].MatD3D;
			resultMesh->meshMaterials()[i].Ambient = resultMesh->meshMaterials()[i].Diffuse;
			if (materials[i].pTextureFilename != NULL)
			{
				if (FAILED(D3DXCreateTextureFromFileA(d3ddev, materials[i].pTextureFilename, &resultMesh->meshTexture()[i])))
				{
					Utils::DebugLogMessage("IMAGE NOT FOUND");
					resultMesh->meshTexture()[i] = NULL;
				}
			}
			else
			{
				resultMesh->meshTexture()[i] = NULL;
			}
		}
	}


	materialBuffer->Release();

	addMesh(resultMesh);

	return resultMesh;
}

