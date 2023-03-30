#pragma once
class InitText
{
private:

	ID3DXFont* font = NULL;

public:

	ID3DXFont* initText(LPDIRECT3DDEVICE9 d3ddev);

	~InitText() { delete font; }

};

