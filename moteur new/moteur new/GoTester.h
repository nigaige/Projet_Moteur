#pragma once


class GoTester : public Component
{
private:
	Input* InputManager = nullptr;
public :
	GoTester(Input* IM, GameObject* go);


	void update();
};

