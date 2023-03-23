#pragma once


class GoTester : public Component
{
private:
	Input* InputManager = nullptr;
public :
	GoTester();


	void update();
};

