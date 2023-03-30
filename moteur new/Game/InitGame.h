#pragma once
class InitGame : public Component
{
private:
	Moteur* moteur_;


public:
	InitGame(Moteur* moteur);
	void update();
	void init();
};
