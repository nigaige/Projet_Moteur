#pragma once
#include <Utils.h>

class Tube
{
public:	
	void initRoad(Mesh* mesh);
	GameObject* GetGO();
	void move();


private: 

	Mesh* meshRoad;
	GameObject* road;


};

