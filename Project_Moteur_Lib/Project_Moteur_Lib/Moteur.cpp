#include "Moteur.h"


void Moteur::init(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nCmdShow,int SCREEN_WIDTH,int SCREEN_HEIGHT)
{
	ZeroMemory(&wc, sizeof(WNDCLASSEX));

    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.hCursor = LoadCursor(NULL, IDC_CROSS);
    wc.lpszClassName = L"WindowClass";

    RegisterClassEx(&wc);


    hWnd = CreateWindowEx(NULL, L"WindowClass", L"Our Direct3D Program",
        WS_OVERLAPPEDWINDOW, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT,
        NULL, NULL, hInstance, NULL);

    ShowWindow(hWnd, nCmdShow);


    SWidth = SCREEN_WIDTH;
    SHeight = SCREEN_HEIGHT;

    // set up and initialize Direct3D
    initD3D(hWnd);
}

void Moteur::initD3D(HWND hWnd)
{
    d3d = Direct3DCreate9(D3D_SDK_VERSION);

    D3DPRESENT_PARAMETERS d3dpp;

    ZeroMemory(&d3dpp, sizeof(d3dpp));
    d3dpp.Windowed = TRUE;
    d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    d3dpp.hDeviceWindow = hWnd;
    d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
    d3dpp.BackBufferWidth = SWidth;
    d3dpp.BackBufferHeight = SHeight;
    d3dpp.EnableAutoDepthStencil = TRUE;
    d3dpp.AutoDepthStencilFormat = D3DFMT_D16;

    // create a device class using this information and the info from the d3dpp stuct
    d3d->CreateDevice(D3DADAPTER_DEFAULT,
        D3DDEVTYPE_HAL,
        hWnd,
        D3DCREATE_HARDWARE_VERTEXPROCESSING,
        &d3dpp,
        &d3ddev);

    init_light();    // call the function to initialize the light and material

    d3ddev->SetRenderState(D3DRS_LIGHTING, TRUE);    // turn on the 3D lighting
    d3ddev->SetRenderState(D3DRS_ZENABLE, TRUE);    // turn on the z-buffer
    d3ddev->SetRenderState(D3DRS_AMBIENT, D3DCOLOR_XRGB(50, 50, 50));    // ambient light


}

void Moteur::render(void) 
{


    // -------------------------TODO change gameobjectLIST location-------------------------------

    //TODO opti variable input
    d3ddev->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
    d3ddev->Clear(0, NULL, D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);

    d3ddev->BeginScene();

    // select which vertex format we are using
    d3ddev->SetFVF(CUSTOMFVF);

    //TODO CAMERA INPUT
    setUpRenderCamera();

    for (int i = 0; i < goLisSize; i++) {
        if (gameObjectList[i]->toDisplay()) {

            Vertice* vertToDisplay =  gameObjectList[i]->findComponent<Vertice>();
            
            //Vertice* vertToDisplay = nullptr;
            if (vertToDisplay == nullptr)  continue;

            //TODO material

            // select the vertex and index buffers to use


            d3ddev->SetStreamSource(0, vertToDisplay->GetVBuffer(), 0, sizeof(CUSTOMVERTEX));

            d3ddev->SetTransform(D3DTS_WORLD, gameObjectList[i]->transform()->GetRendu());

            LPDIRECT3DINDEXBUFFER9 indices = vertToDisplay->GetIBuffer();
            if (indices == NULL) {
                d3ddev->DrawPrimitive(vertToDisplay->GetPrimitvMethode(), 0, vertToDisplay->GetNbPrimitives());
            }
            else {
                d3ddev->SetIndices(indices);
                d3ddev->DrawIndexedPrimitive(vertToDisplay->GetPrimitvMethode(), 0, 0, vertToDisplay->GetNbVertex(), 0, vertToDisplay->GetNbPrimitives());
            }
        }
    }

    d3ddev->EndScene();

    d3ddev->Present(NULL, NULL, NULL, NULL);


}



void Moteur::setUpRenderCamera() {

    //TODO TAKE CAMERA OBJECT POS ARGUMENT
    // set the view transform
    D3DXMATRIX matView;    // the view transform matrix

    D3DXVECTOR3 pEye(0.0f, 5.0f, 15.0f);
    D3DXVECTOR3 pAt(0.0f, 0.0f, 0.0f);
    D3DXVECTOR3 pUp(0.0f, 1.0f, 0.0f);


    D3DXMatrixLookAtLH(&matView,
        &pEye,    // the camera position
        &pAt,    // the look-at position
        &pUp);    // the up direction
    d3ddev->SetTransform(D3DTS_VIEW, &matView);    // set the view transform to matView
    d3ddev->SetTransform(D3DTS_VIEW, &matView);    // set the view transform to matView

    // set the projection transform
    D3DXMATRIX matProjection;    // the projection transform matrix
    D3DXMatrixPerspectiveFovLH(&matProjection,
        D3DXToRadian(45),    // the horizontal field of view
        (FLOAT)SWidth / (FLOAT)SHeight, // aspect ratio
        1.0f,    // the near view-plane
        100.0f);    // the far view-plane
    d3ddev->SetTransform(D3DTS_PROJECTION, &matProjection);     // set the projection


}

void Moteur::addGameObject(GameObject* GO)
{
    gameObjectList.push_back(GO);
    goLisSize++;
}


void Moteur::cleanD3D(void)
{
    d3ddev->Release();    // close and release the 3D device
    d3d->Release();    // close and release Direct3D
}

void Moteur::init_light(void)
{
    //TODO ITERATE

    D3DLIGHT9 light;    // create the light struct
    D3DMATERIAL9 material;    // create the material struct

    ZeroMemory(&light, sizeof(light));    // clear out the light struct for use
    light.Type = D3DLIGHT_DIRECTIONAL;    // make the light type 'directional light'
    light.Diffuse = D3DXCOLOR(255.0f, 0.5f, 0.5f, 1.0f);    // set the light's color
    light.Direction = D3DXVECTOR3(-1.0f, -0.3f, -1.0f);

    d3ddev->SetLight(0, &light);    // send the light struct properties to light #0
    d3ddev->LightEnable(0, TRUE);    // turn on light #0

    ZeroMemory(&material, sizeof(D3DMATERIAL9));    // clear out the struct for use
    material.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);    // set diffuse color to white
    material.Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);    // set ambient color to white

    d3ddev->SetMaterial(&material);    // set the globably-used material to &material
}

void Moteur::addMeshToscene(Vertice* verti)
{


    //----------------VBUFFER
    d3ddev->CreateVertexBuffer(verti->verticeSize(),
        0,
        CUSTOMFVF,
        D3DPOOL_MANAGED,
        &v_buffer,
        NULL);

    VOID* pVoid;    // a void pointer

    // lock v_buffer and load the vertices into it
    v_buffer->Lock(0, 0, (void**)&pVoid, 0);
    memcpy(pVoid, verti->vertex(), verti->verticeSize());
    v_buffer->Unlock();
    
    verti->SetVBuffer(v_buffer);


    //----------------IBUFFER
    d3ddev->CreateIndexBuffer(sizeof(indices),
        0,
        D3DFMT_INDEX16,
        D3DPOOL_MANAGED,
        &i_buffer,
        NULL);


    // lock v_buffer and load the vertices into it
    v_buffer->Lock(0, 0, (void**)&pVoid, 0);
    memcpy(pVoid, verti->indice(), indices);
    v_buffer->Unlock();

}
