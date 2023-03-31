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


    delete Ibuffer_;
    delete Vbuffer_;

    Utils::DeleteVector(vertex_);

        
    delete meshMaterials_;
    delete meshTexture_;



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
