#pragma once
class Ui
{
private:
	ID3DXFont* font = Moteur::getFont();
	RECT fRectangle_;
	std::string message_;

public:

	void Draw();
	Ui(RECT frectangle, std::string message);
	~Ui();
};

