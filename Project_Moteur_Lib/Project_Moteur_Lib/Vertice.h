#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include "Component.h"
#include "Transform.h"

struct CUSTOMVERTEX { FLOAT X, Y, Z; D3DVECTOR NORMAL; };
#define CUSTOMFVF (D3DFVF_XYZ | D3DFVF_NORMAL)



class Vertice: public Component
{
private: 
	LPDIRECT3DINDEXBUFFER9 i_buffer;
	LPDIRECT3DVERTEXBUFFER9 v_buffer;
	D3DPRIMITIVETYPE primitivMethode_;
	int nbVertex = 0;
	int nbPrimitives = 0;

public:
	Vertice();
	//TODO load fromFile

	void init_graphics(LPDIRECT3DDEVICE9 d3ddev, D3DPRIMITIVETYPE primitivMethode, CUSTOMVERTEX vertices[], short indices[]);
	
	void Draw(LPDIRECT3DDEVICE9 d3ddev);

	int DeduceTriangle(CUSTOMVERTEX vertices[]);

	LPDIRECT3DVERTEXBUFFER9 GetVBuffer();
	LPDIRECT3DINDEXBUFFER9 GetIBuffer();
	void SetVBuffer(LPDIRECT3DVERTEXBUFFER9 v_buffer);

	D3DPRIMITIVETYPE GetPrimitvMethode();
	int GetNbPrimitives();
	int GetNbVertex();
};

