#pragma once



#define FORWARD		D3DXVECTOR3(1.0f, 0.0f, 0.0f)
#define BACKWARD	D3DXVECTOR3(-1.0f, 0.0f, 0.0f)
#define RIGHT		D3DXVECTOR3(0.0f, 0.0f, 1.0f)
#define LEFT		D3DXVECTOR3(0.0f, 0.0f, -1.0f)
#define UP			D3DXVECTOR3(0.0f, 1.0f, 0.0f)
#define DOWN		D3DXVECTOR3(0.0f, -1.0f,0.0f )




class Transform
{
private:
	D3DXVECTOR3 v_position_;
	D3DXVECTOR3 v_anchorPoint_position_;
	D3DXVECTOR3 v_scale_;

	D3DXMATRIX m_position_;
	D3DXMATRIX m_anchorPoint_position_;
	D3DXMATRIX m_scale_;
	D3DXQUATERNION q_rotation_;

	//float roll_, yaw_, pitch_;
	D3DXVECTOR3* v_forward_;
	D3DXVECTOR3* v_up_;
	D3DXVECTOR3* v_right_;
	D3DXMATRIX m_rotation_;


	D3DXMATRIX m_Transform_;//Final Value

public:
	Transform();
	~Transform();//TODO

	//TODO function add value

	//----------position--------
	D3DXVECTOR3 position();
	void position(D3DXVECTOR3 newPos);
	void posX(float x);
	void posY(float y);
	void posZ(float z);
	void updatePosition();


	//----------Scale-----------
	D3DXVECTOR3 scale();
	void scale(D3DXVECTOR3 newPos);
	void scaleX(float x);
	void scaleY(float y);
	void scaleZ(float z);
	void updateScale();

	//---------Rotation---------
	D3DXMATRIX rotation();
	void addPitch(float pitch);
	void addRoll(float roll);
	void addYaw(float yaw);
	void addRollPitchYaw(float pitch, float roll, float yaw);
	D3DXVECTOR3* forward();
	D3DXVECTOR3* right();
	D3DXVECTOR3* up();
	D3DXQUATERNION genRotation(float roll = NULL, float pitch = NULL, float yaw = NULL);
	void setARotation(float roll = NULL, float pitch = NULL, float yaw = NULL);
	void getARotation(float roll = NULL, float pitch = NULL, float yaw = NULL);

	//---------FINAL-------------
	void updateFinal();

	D3DXMATRIX* displayValue();//Final Value


	//-------UTILS--------------
	std::string toString();
	std::string posToString();
	std::string ScaToString();
	std::string rotToString();




};