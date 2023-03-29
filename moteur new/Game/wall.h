#pragma once
class Wall : public Component
{

public :
	Wall(Moteur* moteur, Shader* color, Mesh* WallMesh);
	~Wall();
	void update(); 
};

