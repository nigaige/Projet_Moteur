#include "tube.h"

void Tube::initRoad(Mesh* mesh)
{
	road = new GameObject;
	meshRoad = mesh;

	road->addComponent(mesh);
}

GameObject* Tube::GetGO()
{
	return road;
}

void Tube::move()
{
	road->transform()->posZ(road->transform()->position().y - 1.0f);
}
