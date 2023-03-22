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


	LPD3DXMESH importedMesh_ = nullptr;
	LPD3DXBUFFER* material_ = nullptr;
	DWORD* matCount_ = 0;

public:
	Mesh(D3DPRIMITIVETYPE primitivMethode);
	~Mesh();

	void addVertex(CUSTOMVERTEX* v);
	void addvector(D3DXVECTOR3* v);

	
	//	GETTER/SETTER
	std::vector<CUSTOMVERTEX*>* vertex()		{ return &vertex_; }
	D3DPRIMITIVETYPE primitivMethode()			{ return primitivMethode_; }
	void Primitiv(int face)						{ Primitiv_ = face; }
	int Primitiv()								{ return Primitiv_; }
	void pointCount(int point)					{ pointCount_ = point; }
	int pointCount()							{ return pointCount_; }

	LPD3DXMESH importedMesh()					{ return importedMesh_; }
	void importedMesh(LPD3DXMESH mesh)			{ importedMesh_ = mesh; }
	LPD3DXBUFFER* material()					{ return material_; }
	void material(LPD3DXBUFFER* material)		{ material_ = material; }
	DWORD* matCount()							{ return matCount_; }
	void matCount(DWORD* matCount)				{ matCount_ = matCount; }



	LPDIRECT3DINDEXBUFFER9 Ibuffer()			{ return Ibuffer_; }
	LPDIRECT3DVERTEXBUFFER9 Vbuffer()			{ return Vbuffer_; }
	void Ibuffer(LPDIRECT3DINDEXBUFFER9 buff)	{ Ibuffer_ = buff; }
	void Vbuffer(LPDIRECT3DVERTEXBUFFER9 buff)	{ Vbuffer_ = buff; }

	void deduceTriangle();



	



};
