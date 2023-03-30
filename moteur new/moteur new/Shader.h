#pragma once

class Shader
{
private:
	LPD3DXEFFECT shaderBuffer_ = nullptr;

	D3DXHANDLE handleTechnique_ = nullptr;
	D3DXHANDLE handleMatrixWVP_ = nullptr;
	std::string path_;

public:

	Shader(std::string path);
	~Shader();

	LPD3DXEFFECT shaderBuffer()						{ return shaderBuffer_; }
	void shaderBuffer(LPD3DXEFFECT sb)				{shaderBuffer_ = sb; }
	D3DXHANDLE* handleTechnique()					{ return &handleTechnique_; }
	D3DXHANDLE* handleMatrixWVP()					{ return &handleMatrixWVP_; }
	void		handleMatrixWVP(D3DXHANDLE htm)		{ handleMatrixWVP_ = htm; }
	void		handleTechnique(D3DXHANDLE ht)		{ handleTechnique_ = ht; }

	void SetMatrix(D3DXMATRIX* wvpMat);

	std::string path()								{ return path_; }

};
