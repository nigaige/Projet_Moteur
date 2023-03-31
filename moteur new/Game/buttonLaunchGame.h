#pragma once
class buttonLaunchGame : public Ui
{
private:	


	int windowWidth;
	int windowHeight;
	RECT windowSize;
	InitMenu* title;

	bool ok = true;
	Moteur* moteur_ = nullptr;
public:
	buttonLaunchGame(Moteur* moteur);
	~buttonLaunchGame();
	void LaunchGame();
	void update();

};

