#pragma once


class Camera : public Component
{
private:
	D3DXVECTOR3 pEye;
	D3DXVECTOR3 pAt;
	D3DXVECTOR3 pUp;

	D3DXMATRIX matView;    // the view transform matrix

	int i_fov_;
	float i_nearViewPlane_;
	float i_farViewPlane_;

public:
	Camera(int Fov, int nearVIewPlane, int farViewPlane);
	~Camera();
	void updateCamera();
	D3DXMATRIX* getMatView();

	int fov();
	void setFov(int newfov);
	float nearViewPlane();
	void setNearViewPlane(int newNearVIewPlane);
	float farViewPlane();
	void setFarViewPlane(int newFarViewPlane);
};