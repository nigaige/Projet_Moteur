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

void Shader::LoadShader(LPDIRECT3DDEVICE9* d3ddev)
{
	LPD3DXEFFECT shaderBuff;
	
	ID3DXBuffer* errors = NULL;

	HRESULT hr = D3DXCreateEffectFromFileA(
		*d3ddev, // Pointeur vers l'interface du périphérique Direct3D
		path_.c_str(), // Nom du fichier HLSL
		NULL, // Tableau des macros de préprocesseur (optionnel)
		NULL, // Interface de rappel pour les messages (optionnel)
		D3DXSHADER_PACKMATRIX_COLUMNMAJOR | D3DXSHADER_DEBUG, // Options de compilation
		NULL, // Interface de gestion de compilation (optionnel)
		&shaderBuff, // Pointeur vers l'effet créé
		&errors // Pointeur vers le buffer d'erreur (optionnel)
	);
	if (hr == D3D_OK)
	{
		handleTechnique_ = shaderBuff->GetTechniqueByName("Default");
		handleMatrixWVP_ = shaderBuff->GetParameterByName(handleMatrixWVP_, "worldViewProj");
		
	}
	
	shaderBuffer_ = shaderBuff;
}
