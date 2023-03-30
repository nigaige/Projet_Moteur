#include "Utils.h"

LevelGenerator::LevelGenerator(Moteur* moteur)
{
	moteur_ = moteur;
	CubeMesh = moteur->ImportingModel("./Mesh/cube.x");
	Playermesh = moteur->ImportingModel("./Mesh/BONGUSV2.x");
	CylinderMesh = moteur->ImportingModel("./Mesh/CylinderRail.x");
	CylinderMesh = moteur->ImportingModel("./Mesh/CylinderRail.x");

	Shader* Red = moteur->LoadShader("./Shader/Red.hlsl");
	Shader* Green = moteur->LoadShader("./Shader/Green.hlsl");
	Shader* Blue = moteur->LoadShader("./Shader/Blue.hlsl");
	Shader* Yellow = moteur->LoadShader("./Shader/Yellow.hlsl");
	Shader* Pink = moteur->LoadShader("./Shader/Pink.hlsl");
}

LevelGenerator::~LevelGenerator(){}

void LevelGenerator::GenerateLevel()
{
	FirstSection();
}

void LevelGenerator::FirstSection()
{
	GameObject* allCylinders[10];

	for (int x = 0; x < 10; ++x) 
	{
		allCylinders[x] = CreateGameObject::Floor(*CylinderMesh);
		moteur_->addGameObject(allCylinders[x]);
	}
}
