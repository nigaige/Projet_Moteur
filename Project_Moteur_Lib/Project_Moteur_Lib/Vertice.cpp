#include "Vertice.h"

Vertice::Vertice()
{}

void Vertice::init_graphics(LPDIRECT3DDEVICE9 d3ddev, LPDIRECT3DVERTEXBUFFER9 v_buffer, LPDIRECT3DINDEXBUFFER9 i_buffer)
{

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
    memcpy(pVoid, vertices, sizeof(vertices));
    v_buffer->Unlock();

    //TODO change content based on vertice amount
    // create the indices using an int array
    short indices[] =
    {
        0, 1, 2,    // side 1
        2, 1, 3,
        4, 5, 6,    // side 2
        6, 5, 7,
        8, 9, 10,    // side 3
        10, 9, 11,
        12, 13, 14,    // side 4
        14, 13, 15,
        16, 17, 18,    // side 5
        18, 17, 19,
        20, 21, 22,    // side 6
        22, 21, 23,
    };

    // create an index buffer interface called i_buffer
    d3ddev->CreateIndexBuffer(36 * sizeof(short),
        0,
        D3DFMT_INDEX16,
        D3DPOOL_MANAGED,
        &i_buffer,
        NULL);

    // lock i_buffer and load the indices into it
    i_buffer->Lock(0, 0, (void**)&pVoid, 0);
    memcpy(pVoid, indices, sizeof(indices));
    i_buffer->Unlock();
    iBuffer = i_buffer;
}

void Vertice::Draw(LPDIRECT3DDEVICE9 d3ddev){
    d3ddev->SetIndices(iBuffer);
    //d3ddev->SetTransform(D3DTS_WORLD, &temp);

    d3ddev->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 24, 0, 12);

}


