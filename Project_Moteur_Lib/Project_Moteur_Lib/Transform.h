#pragma once
#include <windows.h>
#include <windowsx.h>
#include <d3d9.h>
#include <d3dx9.h>
#define _USE_MATH_DEFINES

#include <cmath>
#include <iostream>
using namespace std;
class Transform
{

private :
	D3DXVECTOR3 vPosition ;
	D3DXVECTOR3 vScale;

	D3DXMATRIX mRot;
	D3DXMATRIX mScale;
	D3DXMATRIX mPos ;
	D3DXMATRIX mRendu;

	float Roll, Yaw, Pitch;

	D3DXQUATERNION quatRot;
	D3DXVECTOR3 vDir = D3DXVECTOR3(1.0f,0.0f,0.0f);
	D3DXVECTOR3 vRight = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	D3DXVECTOR3 vUp = D3DXVECTOR3(0.0f, 0.0f, 1.0f);

public:
	Transform();
	~Transform();
	void SetvPos(D3DXVECTOR3 NewPos);
	void SetvScale(D3DXVECTOR3 NewScale);

	D3DXVECTOR3 GetvPos();
	D3DXVECTOR3 GetvScale();

	void UpdateRendu();
	D3DXMATRIX GetRendu();



	void SetRotation(float NewYaw, float NewPitch, float NewRoll );
	float DegToRad(float Angle);

	

};

