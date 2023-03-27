#pragma once
class Camera : public Component
{
private:
	D3DXVECTOR3 pEye;
	D3DXVECTOR3 pAt;
	D3DXVECTOR3 pUp;

	D3DXMATRIX matView_;
	D3DXMATRIX matProj_;

	int i_fov_;
	float i_nearViewPlane_;
	float i_farViewPlane_;

public:
	Camera(int Fov, float nearVIewPlane, float farViewPlane);
	~Camera();
	D3DXMATRIX* updateCamera();

	int fov();
	void setFov(int newfov);
	float nearViewPlane();
	void nearViewPlane(float newNearVIewPlane);
	float farViewPlane();
	void farViewPlane(float newFarViewPlane);

	void matView(D3DXMATRIX* matView)										{ matView_ = *matView; }
	void matProj(D3DXMATRIX* matProj)										{ matProj_ = *matProj; }
	D3DXMATRIX* matView()													{ return &matView_; }
	D3DXMATRIX* matProj()													{ return &matView_; }
};

