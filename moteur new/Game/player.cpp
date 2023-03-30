#include "Utils.h"

Player::Player() 
{
}

void Player::MovePlayer()
{
	if (Moteur::inputManager_->getKeyState('Z') == States::HOLD)
	{
		z++;
		transform_->position(D3DXVECTOR3(0.f, 0.f, z));
	}
}

void Player::update() 
{
	MovePlayer();
;}


