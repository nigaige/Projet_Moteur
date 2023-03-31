#include "Utils.h";



InitMenu::InitMenu(Moteur* moteur)
{
	moteur_ = moteur;
	message_ = "Best game of the world";
	SetRect(&fRectangle_, 50, 100, 400, 600);
}


void InitMenu::update()
{

}
