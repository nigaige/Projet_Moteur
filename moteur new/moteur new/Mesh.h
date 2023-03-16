#pragma once
#include "Utils.h"



class Mesh : public Component
{
private:

	LPDIRECT3DINDEXBUFFER9 Ibuffer_ = NULL;
	LPDIRECT3DVERTEXBUFFER9 Vbuffer_ = NULL;
	D3DPRIMITIVETYPE primitivMethode_;
	int Primitiv_ = 0;
	std::vector<CUSTOMVERTEX*> vertex_;
public:
	Mesh(D3DPRIMITIVETYPE primitivMethode);

	void addVertex(CUSTOMVERTEX* v);

	
	//	GETTER/SETTER
	std::vector<CUSTOMVERTEX*>* vertex()		{ return &vertex_; }
	D3DPRIMITIVETYPE primitivMethode()			{ return primitivMethode_; }
	int Primitiv()								{ return Primitiv_; }


	LPDIRECT3DINDEXBUFFER9 Ibuffer()			{ return Ibuffer_; }
	LPDIRECT3DVERTEXBUFFER9 Vbuffer()			{ return Vbuffer_; }
	void Ibuffer(LPDIRECT3DINDEXBUFFER9 buff)	{ Ibuffer_ = buff; }
	void Vbuffer(LPDIRECT3DVERTEXBUFFER9 buff)	{ Vbuffer_ = buff; }




};

