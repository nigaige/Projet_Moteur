#include "GoTester.h"

void GoTester::update()
{
	if (InputManager->getKeyState('A') == States::HOLD) {
		gameobject->transform()->pitch(gameobject->transform()->pitch()+0.1f);
	};



}

GoTester::GoTester(Input* IM, GameObject* go) {
	gameobject = go;
	InputManager = IM;
}
