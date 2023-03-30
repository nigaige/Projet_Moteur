#include "Utils.h"


Ui::Ui()
{
}

void Ui::Draw()
{
	font->DrawTextA(NULL, message_.c_str(), -1, &fRectangle_, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255));
}


Ui::~Ui()
{
}
