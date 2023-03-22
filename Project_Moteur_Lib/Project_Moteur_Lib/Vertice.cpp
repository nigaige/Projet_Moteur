#include "Vertice.h"

Vertice::Vertice(CUSTOMVERTEX* vertex,int pointCount, D3DPRIMITIVETYPE primitivMethode)
{
    vertex_ = vertex;
 

    verticeSize_ = pointCount;
    primitivMethode_ = primitivMethode;
    nbVertex = pointCount;
    nbPrimitives = DeduceTriangle(vertex_);
    
    

}



int Vertice::DeduceTriangle(CUSTOMVERTEX vertices[]){
    int size = nbVertex;

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

    return size;
}

LPDIRECT3DVERTEXBUFFER9 Vertice::GetVBuffer()
{
    return v_buffer ;
}
LPDIRECT3DINDEXBUFFER9 Vertice::GetIBuffer()
{
    return i_buffer ;
}

void Vertice::SetVBuffer(LPDIRECT3DVERTEXBUFFER9 newv_buffer)
{
    v_buffer = newv_buffer;
}

void Vertice::SetIBuffer(LPDIRECT3DINDEXBUFFER9 newi_buffer)
{
    i_buffer = newi_buffer;
}

D3DPRIMITIVETYPE Vertice::GetPrimitvMethode()
{
    return primitivMethode_;
}

int Vertice::GetNbPrimitives()
{
    return nbPrimitives;
}

int Vertice::GetNbVertex()
{
    return nbVertex;
}



