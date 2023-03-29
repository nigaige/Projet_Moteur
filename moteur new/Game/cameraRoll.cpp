#include "Utils.h";

void cameraRoll::update()
{
}

cameraRoll::cameraRoll()
{
	if (Moteur::inputManager_->getKeyState('A') == States::HOLD) {
		//transform_->addPitch(0.1f);
		transform_->addRoll(0.1f);
		//transform_->addYaw(0.1f);
	};

	if (Moteur::inputManager_->getKeyState('E') == States::HOLD) {
		//transform_->addPitch(-0.1f);
		transform_->addRoll(-0.1f);
		//transform_->addRoll(0.1f);
	};
}
