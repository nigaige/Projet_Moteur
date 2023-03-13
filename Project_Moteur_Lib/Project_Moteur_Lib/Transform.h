#pragma once
#include <windows.h>
#include <windowsx.h>
#include <d3d9.h>
#include <d3dx9.h>
class Transform
{

private :
	D3DXVECTOR3 vPosition ;
	D3DXVECTOR3 vScale;
	D3DXMATRIX mRendu;


	float Roll, Yaw, Pitch;

	D3DXQUATERNION quat;
		

public:
	void SetvPos(D3DXVECTOR3 NewPos);
	void SetvScale(D3DXVECTOR3 NewScale);

	D3DXVECTOR3 GetvPos();
	D3DXVECTOR3 GetvScale();

	void UpdateRendu();
	D3DXMATRIX GetRendu();



	void Rotate(float NewYaw, float NewPitch, float NewRoll );



};

