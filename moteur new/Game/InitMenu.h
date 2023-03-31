#pragma once
class InitMenu : public Ui
{

private : 
	Moteur* moteur_;

public:
	InitMenu(Moteur* moteur);
	void update();
};

