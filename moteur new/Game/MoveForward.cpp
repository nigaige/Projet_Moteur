#include "Utils.h"

void MoveForward::update()
{
	Utils util;
	util.DebugLogMessage("ok");
	//transform()->posZ(transform()->position().z + velocity_);
	/*
	if (transform()->position().z < -20.0f)
	{
		transform()->position(D3DXVECTOR3(transform()->position().x, transform()->position().y,80.f));
	}
	*/
	if (Moteur::inputManager_->getKeyState('Z') == States::HOLD) {
		//transform_->addPitch(-0.1f);
		transform()->posX(transform()->position().x + velocity_);
		//transform_->addRoll(0.1f);
	};
	if (Moteur::inputManager_->getKeyState('s') == States::HOLD) {
		//transform_->addPitch(-0.1f);
		transform()->posX(transform()->position().x - velocity_);
		//transform_->addRoll(0.1f);
	};
}


MoveForward::MoveForward() {

}