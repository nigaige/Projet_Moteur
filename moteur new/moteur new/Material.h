#include "Shader.h"

class Material
{
	Shader* shader;

	Material();
	~Material();

	void SetMaterial(Shader* newShader);
	Shader GetMaterial();

};