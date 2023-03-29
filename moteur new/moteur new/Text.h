#pragma once
class Text : public Component
{
private:
	ID3DXFont* font = Moteur::getFont();
	RECT fRectangle;
	std::string message;

public:

	void update();
	Text();
	~Text();
};

