#pragma once

#include <windows.h>
#include <windowsx.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <string>
#include "Utils.h"
#include <WinNT.h>
#include <iostream>
#include <fstream>
#include "Utils.h"

class Shader
{
private:
	LPD3DXBUFFER shaderContent;
	LPDIRECT3DDEVICE9 _d3ddev;

public:

	Shader(LPDIRECT3DDEVICE9 d3ddev);
	~Shader();

	//Charge le shader grâce à un contenu.
	void LoadShader(LPD3DXBUFFER shaderContent_);

	//Charge le shader grâce au chemin.
	void LoadShader(std::string* shaderPath);
};

