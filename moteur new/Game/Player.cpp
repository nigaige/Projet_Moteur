#include "Utils.h"

Player::Player(){}

Player::~Player(){}

void Player::update()
{
    /*if(Moteur::inputManager_->getKeyState('Z') == HOLD)
    {
        z++;
        transform_->posZ(transform_->position().z - z);
    }*/

    if(Moteur::inputManager_->getKeyState('D') == HOLD)
    {
        roll++;
        transform_->addRoll(z);
    }
}

