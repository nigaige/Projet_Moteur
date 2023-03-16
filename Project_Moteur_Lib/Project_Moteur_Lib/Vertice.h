#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include "Component.h"
#include "Transform.h"
#include "Utils.h"

#define CUSTOMFVF (D3DFVF_XYZ | D3DFVF_NORMAL)



class Vertice: public Component
{
private: 
	LPDIRECT3DINDEXBUFFER9 i_buffer		= NULL;
	LPDIRECT3DVERTEXBUFFER9 v_buffer	= NULL;
	D3DPRIMITIVETYPE primitivMethode_;
	int nbVertex = 0;
	int nbPrimitives = 0;
	CUSTOMVERTEX* vertex_ = nullptr;
	int verticeSize_ = 0;


public:
	Vertice(CUSTOMVERTEX* vertex, int pointCount, D3DPRIMITIVETYPE primitivMethode);
	//TODO load fromFile
	CUSTOMVERTEX* vertex() { return vertex_; }
	int verticeSize() { return verticeSize_; }

	int DeduceTriangle(CUSTOMVERTEX vertices[]);

	LPDIRECT3DVERTEXBUFFER9 GetVBuffer();
	LPDIRECT3DINDEXBUFFER9 GetIBuffer();
	void SetVBuffer(LPDIRECT3DVERTEXBUFFER9 v_buffer);
	void SetIBuffer(LPDIRECT3DINDEXBUFFER9 i_buffer);

	D3DPRIMITIVETYPE GetPrimitvMethode();
	int GetNbPrimitives();
	int GetNbVertex();
};

