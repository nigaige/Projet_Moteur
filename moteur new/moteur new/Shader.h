#pragma once

class Shader
{
private:
	IDirect3DVertexShader9** _ppShader = nullptr;

public:

	Shader(IDirect3DVertexShader9** ppShader);
	~Shader();

	//Charge le shader gr�ce � un contenu.
	void LoadShader(LPD3DXBUFFER shaderContent_);

	//Charge le shader gr�ce au chemin.
	void LoadShader(std::string* shaderPath);
};
