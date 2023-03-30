#include "Utils.h"

Shader::Shader(std::string path)
{
	path_ = path;
}

Shader::~Shader() {}

void Shader::SetMatrix(D3DXMATRIX* wvpMat)
{
    shaderBuffer_->SetMatrix(handleMatrixWVP_, wvpMat);
}

