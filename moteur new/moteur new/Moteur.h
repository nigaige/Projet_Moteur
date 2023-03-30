#pragma once


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
	std::vector<Ui*> uiElement;

	ColliderManager* colliderManager_;

	GameObject* camera_;
	Camera* cameraComponent;

	InitText* initText;

public:
	HWND gethWnd() { return hWnd; }

    Moteur(HINSTANCE hInstance,
		HINSTANCE hPrevInstance,
		LPWSTR lpCmdLine,
		int nCmdShow);
	~Moteur();

	ColliderManager* colliderManager() { return colliderManager_; }



	void Init();
	void loadMeshInScene(Mesh* MeshToLoad);
	void initD3D();
	void cleanD3D(void);

	void setUpCamera();
	GameObject* camera();

	void addGameObject(GameObject* go);
	void addUiComponent(Ui* ui);
	void rmGamObject(GameObject* go);
	void rmUiComponent(Ui* ui);
	void addMesh(Mesh* me);
	void rmMesh(Mesh* me);

	void setGoList(std::vector<GameObject*> list);
	void setMeList(std::vector<Mesh*> list);

	static ID3DXFont* getFont() { return font;  };
	

	//---------------GAMELOOOP
	void gameLoop();															
	void render(void);
	void update(void);															
	void fixedUpdate(void);															
	void updateTransform(void);

	void LoadShader(Shader* sh);
	void renderMaterial(GameObject* go,Mesh* mesh);										//TODO MANAGE GLOBAL TIME


	Mesh* ImportingModel(std::string path);

	void loadMesh(Mesh* me);

	static float s_deltaTime_;
	static Input* inputManager_;
	static ID3DXFont* font;
};

