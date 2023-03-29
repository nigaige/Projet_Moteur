#include "Utils.h"

ID3DXFont* InitText::initText(LPDIRECT3DDEVICE9 d3ddev)
{
	HRESULT hr = D3DXCreateFontA(d3ddev, 40, 0, FW_NORMAL, 1, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
		ANTIALIASED_QUALITY, FF_DONTCARE, "Arial", &font);
	return font;
}
