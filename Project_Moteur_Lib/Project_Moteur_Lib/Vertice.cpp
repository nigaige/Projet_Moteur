#include "Vertice.h"

Vertice::Vertice(CUSTOMVERTEX* vertex, D3DPRIMITIVETYPE primitivMethode,LPDIRECT3DINDEXBUFFER9 ibuffer = NULL)
{
    vertex_ = vertex;
 

    verticeSize_ = sizeof(vertex);

    nbPrimitives = DeduceTriangle(vertex_);
    nbVertex = sizeof(vertex_) / sizeof(CUSTOMVERTEX);
    primitivMethode_ = primitivMethode;
    
    i_buffer = ibuffer;

}



int Vertice::DeduceTriangle(CUSTOMVERTEX vertices[]){
    int size = sizeof(vertices)/sizeof(CUSTOMVERTEX);

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



