#include "Utils.h"
#include "GoTester.h"

void GoTester::update()
{
	if (InputManager->getKeyState('A') == States::HOLD) {
		//transform_->addPitch(0.1f);
		transform_->addYaw(0.1f);
		//transform_->addRoll(0.1f);
	};
}

GoTester::GoTester(Input* IM) {
	InputManager = IM;
}
