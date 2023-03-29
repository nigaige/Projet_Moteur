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
	LPD3DXBUFFER materialBuffer_ = nullptr;
	DWORD matCount_ = 0;

	D3DMATERIAL9* meshMaterials_ = nullptr;
	LPDIRECT3DTEXTURE9* meshTexture_ = nullptr;
	Shader* shader_ = nullptr;

public:
	Mesh(D3DPRIMITIVETYPE primitivMethode);
	~Mesh();

	void addVertex(CUSTOMVERTEX* v);
	void addvector(D3DXVECTOR3* v);

	
	//	GETTER/SETTER
	std::vector<CUSTOMVERTEX*>* vertex()			{ return &vertex_; }
	D3DPRIMITIVETYPE primitivMethode()				{ return primitivMethode_; }
	void Primitiv(int face)							{ Primitiv_ = face; }
	int Primitiv()									{ return Primitiv_; }
	void pointCount(int point)						{ pointCount_ = point; }
	int pointCount()								{ return pointCount_; }

	LPD3DXMESH importedMesh()						{ return importedMesh_; }
	void importedMesh(LPD3DXMESH mesh)				{ importedMesh_ = mesh; }
	LPD3DXBUFFER materialBuffer()					{ return materialBuffer_; }
	void materialBuffer(LPD3DXBUFFER material)		{ materialBuffer_ = material; }
	DWORD matCount()								{ return matCount_; }
	void matCount(DWORD matCount)					{ matCount_ = matCount; }

	void meshMaterials(D3DMATERIAL9* materials)		{ meshMaterials_ = materials; }
	D3DMATERIAL9* meshMaterials()					{ return meshMaterials_; }
	void meshTexture(LPDIRECT3DTEXTURE9* textures)	{ meshTexture_ = textures; }
	LPDIRECT3DTEXTURE9* meshTexture()				{ return meshTexture_; }

	LPDIRECT3DINDEXBUFFER9 Ibuffer()				{ return Ibuffer_; }
	LPDIRECT3DVERTEXBUFFER9 Vbuffer()				{ return Vbuffer_; }
	void Ibuffer(LPDIRECT3DINDEXBUFFER9 buff)		{ Ibuffer_ = buff; }
	void Vbuffer(LPDIRECT3DVERTEXBUFFER9 buff)		{ Vbuffer_ = buff; }

	Shader* shader()								{ return shader_; }
	void shader(Shader* shader)						{ shader_ = shader; }

	void deduceTriangle();



	



};
