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
	
	float Roll, Yaw, Pitch;

	D3DXQUATERNION quatRot;

	D3DXQUATERNION quat;

	D3DXVECTOR3 vDir = D3DXVECTOR3(1.0f,0.0f,0.0f);
	D3DXVECTOR3 vRight = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	D3DXVECTOR3 vUp = D3DXVECTOR3(0.0f, 0.0f, 1.0f);

	

	D3DXMATRIX mRendu;//Final Value
public:
	Transform();
	~Transform();
	void SetvPos(D3DXVECTOR3 NewPos);
	D3DXVECTOR3 GetvPos();

	void SetvScale(D3DXVECTOR3 NewScale);
	D3DXVECTOR3 GetvScale();

	void SetRotation(float NewYaw, float NewPitch, float NewRoll, bool isRadian = false);
	void CreateRotation(float NewRoll, float NewPitch, float NewYaw, bool isRadian = false);
	float DegToRad(float Angle);
	//TODO GetRotation

	
	void UpdateRendu();
	D3DXMATRIX GetRendu();
	void addRotation(float NewYaw, float NewPitch, float NewRoll, bool isRadian = false);

	void SetRoll(float Angle, bool isRadian = false);
	void SetYaw(float Angle, bool isRadian = false);
	void SetPitch(float Angle, bool isRadian = false);

	void AddRoll(float Angle, bool isRadian = false);
	void AddPitch(float Angle, bool isRadian = false);
	void AddYaw(float Angle, bool isRadian = false);
};

