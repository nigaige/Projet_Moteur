#include "Utils.h"

Shader::Shader(LPD3DXEFFECT shaderBuffer)
{
    shaderBuffer_ = shaderBuffer;
}

Shader::~Shader() {}

void Shader::SetMatrix(D3DXMATRIX* wvpMat)
{
    shaderBuffer_->SetMatrix(handleMatrixWVP_, wvpMat);
}
