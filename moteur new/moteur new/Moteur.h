

class Moteur
{
private:

    LPDIRECT3D9 d3d;    // the pointer to our Direct3D interface
    LPDIRECT3DDEVICE9 d3ddev;    // the pointer to the device class

	HWND hWnd;
	WNDCLASSEX wc;

	int nCmdShow;

	//Mesh* triangle;
	std::vector<GameObject*> GOList;
	std::vector<Mesh*> MeList;

	Input* inputManager_;

public:

    Moteur(HINSTANCE hInstance,
		HINSTANCE hPrevInstance,
		LPSTR lpCmdLine,
		int nCmdShow);
	~Moteur();

	Input* inputManager() { return inputManager_; }




	void Init();
	void loadMeshInScene(Mesh* MeshToLoad);
	void initD3D();
	void cleanD3D(void);

	void setUpCamera();

	void addGameObject(GameObject* go);
	void rmGamObject(GameObject* go);
	void addMesh(Mesh* me);
	void rmMesh(Mesh* me);

	//---------------GAMELOOOP
	void gameLoop();															//TODO
	void render(void);
	void update(void);															//TODO MANAGE GLOBAL TIME

	Shader LoadShader(std::string* shaderPath);
};

