#include "Vertice.h"

Vertice::Vertice()
{
    struct CUSTOMVERTEX { FLOAT X, Y, Z; D3DVECTOR NORMAL; };

}

void Vertice::init_graphics(LPDIRECT3DDEVICE9 d3ddev, D3DPRIMITIVETYPE primitivMethode , CUSTOMVERTEX vertices[], short indices[] = NULL)
{

    nbPrimitives = DeduceTriangle(vertices);
    nbVertex = sizeof(vertices) / sizeof(CUSTOMVERTEX);
    primitivMethode_ = primitivMethode;

    // create a vertex buffer interface called v_buffer
        d3ddev->CreateVertexBuffer(24 * sizeof(CUSTOMVERTEX),
            0,
            CUSTOMFVF,
            D3DPOOL_MANAGED,
            &v_buffer,
            NULL);

        VOID* pVoid;    // a void pointer

        // lock v_buffer and load the vertices into it
        v_buffer->Lock(0, 0, (void**)&pVoid, 0);
        memcpy(pVoid, &vertices, sizeof(vertices));
        v_buffer->Unlock();



        if (indices != NULL) {

            // create an index buffer interface called i_buffer
            d3ddev->CreateIndexBuffer(  sizeof(indices),  
                                        0,
                                        D3DFMT_INDEX16,
                                        D3DPOOL_MANAGED,
                                        &i_buffer,
                                        NULL);

            // lock i_buffer and load the indices into it
            i_buffer->Lock(0, 0, (void**)&pVoid, 0);
            memcpy(pVoid, &indices, sizeof(indices));
            i_buffer->Unlock();

        }
        
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

int Vertice::GetPrimitvMethode()
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


