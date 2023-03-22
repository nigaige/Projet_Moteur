#pragma once

class Material
{
	Shader* shader;

	Material();
	~Material();

	void SetMaterial(Shader* newShader);
	Shader GetMaterial();

};