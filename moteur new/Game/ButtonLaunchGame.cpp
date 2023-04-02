#include "Utils.h";

ButtonLaunchGame::ButtonLaunchGame(Moteur* moteur)
{
	moteur_ = moteur;
	
	message_ = "Start";

    title = new InitMenu(moteur_);
	moteur_->addUiComponent(title);

}

void ButtonLaunchGame::LaunchGame()
{
	GameObject* initGame = new GameObject();

	InitGame* initGameInstance = new InitGame(moteur_);
	
	initGame->addComponent(initGameInstance);
	
	moteur_->addGameObject(initGame);
	moteur_->rmUiComponent(title);
	moteur_->rmUiComponent(this);
}

void ButtonLaunchGame::update()
{

	if (GetWindowRect(moteur_->gethWnd(), &windowSize))
	{
		windowWidth = windowSize.right - windowSize.left;
		windowHeight = windowSize.bottom - windowSize.top;
	}
	SetRect(&fRectangle_, (windowWidth / 2) - 100, (windowHeight / 2) - 100, (windowWidth / 2) + 100, (windowHeight / 2) + 100);

	if (ok == true) { // TODO Check le destroy de cette merde
		if (Moteur::inputManager_->getKeyState(VK_LBUTTON) == States::PRESSED)
		{
			POINT p;
			GetCursorPos(&p);
			if (GetCursorPos(&p))
			{
				ScreenToClient(moteur_->gethWnd(), &p);

				if (p.x < fRectangle_.right && p.x > fRectangle_.left && p.y > fRectangle_.top && p.y < fRectangle_.bottom) 
				{
					LaunchGame();	
					ok = false;
				}
			}
		};

	}

}

