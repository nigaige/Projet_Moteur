#include "Utils.h"

void MoveForward::update()
{
	Utils util;
	
	transform()->posZ(transform()->position().z + velocity_);
	/*
	if (transform()->position().z < -20.0f)
	{
		transform()->position(D3DXVECTOR3(transform()->position().x, transform()->position().y,80.f));
	}
	*/
	if (Moteur::inputManager_->getKeyState('Z') == States::HOLD) {
		//transform_->addPitch(0.1f);
		//transform_->addRoll(0.1f);
		//transform_->addYaw(0.1f);
		transform()->posZ(transform()->position().z + velocity_);
	};


	
}


MoveForward::MoveForward() {

}

MoveForward::~MoveForward()
{
}
