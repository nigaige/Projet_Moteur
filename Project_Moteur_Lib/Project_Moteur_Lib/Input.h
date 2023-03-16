#pragma once
#include <Windows.h>

class Input
{

public:

	enum States
	{
		NOTPRESS,
		HOLD,
		PRESSED,
		RELEASED
	};

	static bool INIT();
	Input::States getKeyState(BYTE keyValue) {};
	void InputUpdate() {};

private:
	static States keys[256];

};

