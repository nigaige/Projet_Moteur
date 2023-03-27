#include "Utils.h"
#include "GoTester.h"

void GoTester::update()
{
	if (Moteur::inputManager_->getKeyState('A') == States::HOLD) {
		//transform_->addPitch(0.1f);
		transform_->addRoll(0.1f);
		//transform_->addRoll(0.1f);
	};
}

GoTester::GoTester() {
}
