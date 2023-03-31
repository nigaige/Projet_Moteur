#pragma once
class InitGame : public Component
{
private:
	Moteur* moteur_;
	GameObject* camera_;
	LevelDesigner* levelCreator;

public:
	InitGame(Moteur* moteur);
	void init();
	void initLevel();
	void initGo();
	void update();
	
};
