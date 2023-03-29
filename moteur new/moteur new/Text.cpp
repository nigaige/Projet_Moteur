#include "Utils.h"


void Text::update()
{
	SetRect(&fRectangle, 0, 0, 400, 600);
	message = "omegalul ça marche";
	font->DrawTextA(NULL, message.c_str(), -1, &fRectangle, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255));
}


Text::Text()
{
}

Text::~Text()
{
}
