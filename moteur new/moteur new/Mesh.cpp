#include "Utils.h"

Mesh::Mesh()
{
}

Mesh::Mesh(D3DPRIMITIVETYPE primitivMethode)
{
	primitivMethode_ = primitivMethode;
}

Mesh::Mesh(std::string path)
{
    path_ = path;
  
}

Mesh::~Mesh()
{
    vertex_.clear();
}

void Mesh::addVertex(CUSTOMVERTEX* v)
{
	vertex_.push_back(v);
}

void Mesh::addvector(D3DXVECTOR3* v)
{
    CUSTOMVERTEX newCustom = { v->x, v->y, v->z, D3DCOLOR_XRGB(255, 0, 255)};
    vertex_.push_back(&newCustom);
}

void Mesh::deduceTriangle() {
    size_t size = vertex_.size();
    switch (primitivMethode_)
    {
    case D3DPT_POINTLIST:
        break;
    case D3DPT_LINELIST:
        size = size / 2;
        break;
    case D3DPT_LINESTRIP:
        size = size - 1;
        break;
    case D3DPT_TRIANGLELIST:
        size = size / 3;
        break;
    case D3DPT_TRIANGLESTRIP:
        size = size - 2;
        break;
    case D3DPT_TRIANGLEFAN:
        size = size - 2;
        break;
    }

    Primitiv_ = size;
}

void Mesh::loadMesh(LPDIRECT3DDEVICE9* d3ddev)
{
    LPD3DXBUFFER materialBuffer = NULL;
    DWORD numMaterial = 0;
    LPD3DXMESH mesh = nullptr;

    HRESULT hr = D3DXLoadMeshFromXA(path_.c_str(), D3DXMESH_MANAGED, *d3ddev, NULL, &materialBuffer, NULL, &numMaterial, &mesh); //Import mesh in meshImp
    if (FAILED(hr))
        Utils::DebugLogMessage("Failed import model");

    importedMesh_ = mesh;
    materialBuffer_ = materialBuffer;
    matCount_ = numMaterial;

    D3DXMATERIAL* materials = (D3DXMATERIAL*)materialBuffer_->GetBufferPointer();
    meshMaterials_ = new D3DMATERIAL9[matCount_];
    meshTexture_ = new LPDIRECT3DTEXTURE9[matCount_];

    if (meshMaterials_ != NULL)
    {
        for (DWORD i = 0; i < matCount_; i++)
        {
            meshMaterials_[i] = materials[i].MatD3D;
            meshMaterials_[i].Ambient = meshMaterials_[i].Diffuse;
            if (materials[i].pTextureFilename != NULL)
            {
                if (FAILED(D3DXCreateTextureFromFileA(*d3ddev, materials[i].pTextureFilename, &meshTexture_[i])))
                {
                    Utils::DebugLogMessage("IMAGE NOT FOUND");
                    meshTexture_[i] = NULL;
                }
            }
            else
            {
                meshTexture_[i] = NULL;
            }
        }
    }

    materialBuffer->Release();
}
