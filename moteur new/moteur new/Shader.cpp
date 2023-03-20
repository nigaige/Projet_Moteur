#pragma once
#include "Utils.h"

Shader::Shader(IDirect3DVertexShader9** ppShader)
{
    _ppShader = ppShader;
}

Shader::~Shader() {}