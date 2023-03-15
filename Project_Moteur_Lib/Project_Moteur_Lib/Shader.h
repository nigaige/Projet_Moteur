#pragma once

#include <string>
#include <d3dx9.h>
#include <WinNT.h>

class Shader
{
private:
	LPD3DXBUFFER shaderContent;

public:

	Shader();
	~Shader();

	//Charge le shader grâce à un contenu.
	void LoadShader(LPD3DXBUFFER shaderContent_);

	//Charge le shader grâce au chemin.
	void LoadShader(std::string* shaderPath);
};

