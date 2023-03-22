#pragma once


class Input
{

private:
	States keys[256];
public:
	Input();
	States gatherKeyState(BYTE keyValue);
	States getKeyState(BYTE keyValue);
	void InputUpdate();

};


