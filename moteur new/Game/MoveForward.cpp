#include "Utils.h"

void MoveForward::update()
{
	Utils util;
	transform()->posZ(transform()->position().z - .50f);

	if (transform()->position().z < -20.0f)
	{
		transform()->position(D3DXVECTOR3(transform()->position().x, transform()->position().y,80.f));
	}
}

MoveForward::MoveForward() {

}