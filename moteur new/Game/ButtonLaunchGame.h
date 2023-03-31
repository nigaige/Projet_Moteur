#pragma once
class ButtonLaunchGame : public Ui
{
private:	


	int windowWidth;
	int windowHeight;
	RECT windowSize;
	InitMenu* title;

	bool ok = true;
	Moteur* moteur_ = nullptr;
public:
	ButtonLaunchGame(Moteur* moteur);
	void LaunchGame();
	void update();

};

