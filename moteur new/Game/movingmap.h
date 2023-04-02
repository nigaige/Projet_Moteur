#pragma once
#include "Utils.h"
class movingmap : public Component
{
private :
	GameObject* Player_;

public:
	void update();
	movingmap(GameObject* Player);
	~movingmap();
};

