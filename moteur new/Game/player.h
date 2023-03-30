#pragma once

class Player : public Component
{
public: 

	Player();

	float z = 0.f;

	void MovePlayer();

	void update();
};

