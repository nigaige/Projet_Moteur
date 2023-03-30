#include "Utils.h";

InitGame::InitGame(Moteur* moteur)
{
	moteur_ = moteur;
}

void InitGame::update()
{
}

void InitGame::init()
{

	Parser* P = new Parser();

	P->Filename("FORMAIN.txt");
	P->ParseAll();
	moteur_->setGoList(P->GOlist);
	moteur_->setMeList(P->MElist);
	moteur_->camera()->addComponent(new playerRoll);

}
