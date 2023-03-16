#pragma once
#include "Utils.h"


#define FORWARD		D3DXVECTOR3(1.0f, 0.0f, 0.0f)
#define BACKWARD	D3DXVECTOR3(-1.0f, 0.0f, 0.0f)
#define RIGHT		D3DXVECTOR3(0.0f, 1.0f, 0.0f)
#define LEFT		D3DXVECTOR3(0.0f, -1.0f, 0.0f)
#define UP			D3DXVECTOR3(0.0f, 0.0f, 1.0f)
#define DOWN		D3DXVECTOR3(0.0f, 0.0f, -1.0f)




class Transform
{
private:
	D3DXVECTOR3 v_position_;
	D3DXVECTOR3 v_scale_;

	D3DXMATRIX m_position_;
	D3DXMATRIX m_scale_;
	D3DXMATRIX m_rotation_;

	float roll_, yaw_, pitch_;


	D3DXMATRIX m_Transform_;//Final Value

public:
	Transform();
	~Transform();//TODO

	//TODO function add value

	//----------position--------
	D3DXVECTOR3 position();
	void position(D3DVECTOR newPos);
	void posX(float x);
	void posY(float y);
	void posZ(float z);
	void updatePosition();

	//----------Scale-----------
	D3DXVECTOR3 scale();
	void scale(D3DVECTOR newPos);
	void scaleX(float x);
	void scaleY(float y);
	void scaleZ(float z);
	void updateScale();

	//---------Rotation---------
	D3DXMATRIX rotation();
	void rotation(D3DXMATRIX newrot);
	void roll(float newRoll);
	void yaw(float newYaw);
	void pitch(float newPitch);
	float roll();
	float yaw();
	float pitch();
	void updateRotation();
	static D3DXMATRIX* getARotation(float roll, float pitch, float yaw, bool isRadian = true);

	//---------FINAL-------------
	void updateFinal();

	D3DXMATRIX* displayValue();//Final Value


	//-------UTILS--------------
	std::string toString();

};

