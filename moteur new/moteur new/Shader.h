#pragma once

class Shader
{
private:
	LPD3DXEFFECT shaderBuffer_ = nullptr;

	D3DXHANDLE handleTechnique_ = nullptr;
	D3DXHANDLE handleMatrixWVP_ = nullptr;

public:

	Shader(LPD3DXEFFECT shaderBuffer);
	~Shader();

	LPD3DXEFFECT shaderBuffer()						{ return shaderBuffer_; }
	D3DXHANDLE* handleTechnique()					{ return &handleTechnique_; }
	D3DXHANDLE* handleMatrixWVP()					{ return &handleMatrixWVP_; }

	void SetMatrix(D3DXMATRIX* wvpMat);

};
