#pragma once

class Shader
{
private:
	IDirect3DVertexShader9** _ppShader = nullptr;

public:

	Shader(IDirect3DVertexShader9** ppShader);
	~Shader();
};
