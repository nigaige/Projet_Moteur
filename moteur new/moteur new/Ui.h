#pragma once
class Ui: public Component
{
protected:
	RECT fRectangle_;
	std::string message_ = "";

private:
	ID3DXFont* font = Moteur::getFont();
	
public:

	Ui();
	void Draw();
	~Ui();
};

