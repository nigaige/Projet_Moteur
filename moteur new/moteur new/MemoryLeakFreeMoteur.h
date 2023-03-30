#pragma once
class MemoryLeakFreeMoteur
{
private:
	LPDIRECT3D9 d3d;    // the pointer to our Direct3D interface
	LPDIRECT3DDEVICE9 d3ddev;    // the pointer to the device class

	HWND hWnd;
	WNDCLASSEX wc;

	std::vector<GameObject*> GOList;
	std::vector<Mesh*> MeList;
	ColliderManager* colliderManager_;
	GameObject* camera_;
	Camera* cameraComponent;

	InitText* initText;


public:
	MemoryLeakFreeMoteur(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow);
	~MemoryLeakFreeMoteur();
	void loop();



	static float s_deltaTime_;
	static Input* inputManager_;
	static ID3DXFont* font;
};

