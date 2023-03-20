#pragma once



class Mesh : public Component
{
private:

	LPDIRECT3DINDEXBUFFER9 Ibuffer_ = NULL;
	LPDIRECT3DVERTEXBUFFER9 Vbuffer_ = NULL;
	D3DPRIMITIVETYPE primitivMethode_;
	int Primitiv_ = 0;
	int pointCount_ = 0;
	std::vector<CUSTOMVERTEX*> vertex_;
public:
	Mesh(D3DPRIMITIVETYPE primitivMethode);
	~Mesh();

	void addVertex(CUSTOMVERTEX* v);
	void addvector(D3DXVECTOR3* v);

	
	//	GETTER/SETTER
	std::vector<CUSTOMVERTEX*>* vertex()		{ return &vertex_; }
	D3DPRIMITIVETYPE primitivMethode()			{ return primitivMethode_; }
	void Primitiv(int face) { Primitiv_ = face; }
	int Primitiv() { return Primitiv_; }
	void pointCount(int point) { pointCount_ = point; }
	int pointCount() { return pointCount_; }


	LPDIRECT3DINDEXBUFFER9 Ibuffer()			{ return Ibuffer_; }
	LPDIRECT3DVERTEXBUFFER9 Vbuffer()			{ return Vbuffer_; }
	void Ibuffer(LPDIRECT3DINDEXBUFFER9 buff)	{ Ibuffer_ = buff; }
	void Vbuffer(LPDIRECT3DVERTEXBUFFER9 buff)	{ Vbuffer_ = buff; }

	void deduceTriangle();








	//FIX
	LPD3DXMESH* MTest = nullptr;

};
