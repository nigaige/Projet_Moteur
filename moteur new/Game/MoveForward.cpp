#include "MoveForward.h"


void MoveForward::update()
{
	Utils util;
	util.DebugLogMessage("ok");
	transform()->posY(transform()->position().y - .10f);

	if (transform()->position().y < -15.0f)
	{
		transform()->position(D3DXVECTOR3(transform()->position().x,80.0f, transform()->position().z));
	}
}

MoveForward::MoveForward() {

}