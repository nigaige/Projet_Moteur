#include "movingmap.h"

void movingmap::update()
{
	if (transform_->position().z - Player_->transform()->position().z <= -42.0f)
	{
		transform_->posZ(transform_->position().z + 80.0f);
	}
}

movingmap::movingmap(GameObject* Player)
{
	Player_ = Player;
}
movingmap::~movingmap()
{
	Player_ = nullptr;
}
