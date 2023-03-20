#pragma once

class Shader
{
private:
	IDirect3DVertexShader9** _ppShader = nullptr;

public:

	Shader(IDirect3DVertexShader9** ppShader);
	~Shader();

	//Charge le shader grâce à un contenu.
	void LoadShader(LPD3DXBUFFER shaderContent_);

	//Charge le shader grâce au chemin.
	void LoadShader(std::string* shaderPath);
};
