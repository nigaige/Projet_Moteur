#include "Utils.h"
#include "GoTester.h"

void GoTester::update()
{
	if (Moteur::inputManager_->getKeyState('A') == States::HOLD) {
		//transform_->addPitch(0.1f);
		//transform_->addYaw(0.1f);
		//transform_->addRoll(0.1f);
		transform_->posX(transform_->position().x + 0.1f);
	};	
	if (Moteur::inputManager_->getKeyState('B') == States::HOLD) {
		//transform_->addPitch(0.1f);
		transform_->addYaw(0.1f);
		//transform_->addRoll(0.1f);
		//transform_->posX(transform_->position().x + 0.1f);
	};
}

GoTester::GoTester() {
}
