#pragma once
class LevelGenerator
{
private:
	Mesh* CubeMesh;
	Mesh* Playermesh;
	Mesh* CylinderMesh;
	Moteur* moteur_;


public:

	LevelGenerator(Moteur* moteur);
	~LevelGenerator();

	void GenerateLevel();

	void FirstSection();

};

