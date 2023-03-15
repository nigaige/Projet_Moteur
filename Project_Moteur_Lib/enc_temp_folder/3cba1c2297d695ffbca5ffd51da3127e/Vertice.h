#pragma once
#include <d3d9.h>
#include <d3dx9.h>
//#include "Source.cpp"
#include "Transform.h"

struct CUSTOMVERTEX { FLOAT X, Y, Z; D3DVECTOR NORMAL; };
#define CUSTOMFVF (D3DFVF_XYZ | D3DFVF_NORMAL)

class Vertice
{
private:
    // create the vertices using the CUSTOMVERTEX struct
   const CUSTOMVERTEX vertices[24] =
    {
        { -3.0f, -3.0f, 3.0f, 0.0f, 0.0f, 1.0f, },    // side 1
        { 3.0f, -3.0f, 3.0f, 0.0f, 0.0f, 1.0f, },
        { -3.0f, 3.0f, 3.0f, 0.0f, 0.0f, 1.0f, },
        { 3.0f, 3.0f, 3.0f, 0.0f, 0.0f, 1.0f, },

        { -3.0f, -3.0f, -3.0f, 0.0f, 0.0f, -1.0f, },    // side 2
        { -3.0f, 3.0f, -3.0f, 0.0f, 0.0f, -1.0f, },
        { 3.0f, -3.0f, -3.0f, 0.0f, 0.0f, -1.0f, },
        { 3.0f, 3.0f, -3.0f, 0.0f, 0.0f, -1.0f, },

        { -3.0f, 3.0f, -3.0f, 0.0f, 1.0f, 0.0f, },    // side 3
        { -3.0f, 3.0f, 3.0f, 0.0f, 1.0f, 0.0f, },
        { 3.0f, 3.0f, -3.0f, 0.0f, 1.0f, 0.0f, },
        { 3.0f, 3.0f, 3.0f, 0.0f, 1.0f, 0.0f, },

        { -3.0f, -3.0f, -3.0f, 0.0f, -1.0f, 0.0f, },    // side 4
        { 3.0f, -3.0f, -3.0f, 0.0f, -1.0f, 0.0f, },
        { -3.0f, -3.0f, 3.0f, 0.0f, -1.0f, 0.0f, },
        { 3.0f, -3.0f, 3.0f, 0.0f, -1.0f, 0.0f, },

        { 3.0f, -3.0f, -3.0f, 1.0f, 0.0f, 0.0f, },    // side 5
        { 3.0f, 3.0f, -3.0f, 1.0f, 0.0f, 0.0f, },
        { 3.0f, -3.0f, 3.0f, 1.0f, 0.0f, 0.0f, },
        { 3.0f, 3.0f, 3.0f, 1.0f, 0.0f, 0.0f, },

        { -3.0f, -3.0f, -3.0f, -1.0f, 0.0f, 0.0f, },    // side 6
        { -3.0f, -3.0f, 3.0f, -1.0f, 0.0f, 0.0f, },
        { -3.0f, 3.0f, -3.0f, -1.0f, 0.0f, 0.0f, },
        { -3.0f, 3.0f, 3.0f, -1.0f, 0.0f, 0.0f, },
    };
	LPDIRECT3DINDEXBUFFER9 iBuffer;
public:
	Vertice();
	//TODO load fromFile

	void init_graphics(LPDIRECT3DDEVICE9 d3ddev, LPDIRECT3DVERTEXBUFFER9 v_buffer, LPDIRECT3DINDEXBUFFER9 i_buffer);
	
	void Draw(LPDIRECT3DDEVICE9 d3ddev);

};

