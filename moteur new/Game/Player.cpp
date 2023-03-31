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

    if(Moteur::inputManager_->getKeyState('A') == HOLD)
    {
        transform_->posY(transform_->position().y + 0.1f);
    }
    
    if(Moteur::inputManager_->getKeyState('E') == HOLD)
    {
        transform_->posY(transform_->position().y - 0.1f);
    }

    if(Moteur::inputManager_->getKeyState('Z') == HOLD)
    {
        transform_->posZ(transform_->position().z - 0.1f);
    }
    
    if(Moteur::inputManager_->getKeyState('S') == HOLD)
    {
        transform_->posZ(transform_->position().z + 0.1f);
    }

    if(Moteur::inputManager_->getKeyState('Q') == HOLD)
    {
        transform_->posX(transform_->position().x + 0.1f);
    }
    
    if(Moteur::inputManager_->getKeyState('D') == HOLD)
    {
        transform_->posX(transform_->position().x - 0.1f);
    }

    if(Moteur::inputManager_->getKeyState('W') == HOLD)
    {
        transform_->addRoll(-0.1f);
    }
    
    if(Moteur::inputManager_->getKeyState('C') == HOLD)
    {
        transform_->addRoll(0.1f);
    }

}

