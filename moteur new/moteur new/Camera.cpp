#include "Utils.h"

Camera::Camera(int Fov, float nearVIewPlane, float farViewPlane) {


	pEye = D3DXVECTOR3(0.0f, 0.0f, 20.0f);
	pAt = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pUp = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	i_fov_ = Fov;
	i_nearViewPlane_ = nearVIewPlane;
	i_farViewPlane_ = farViewPlane;
}


Camera::~Camera() {
	/*delete pEye;
	delete pAt;
	delete pUp;
	delete matView_;
	delete matProj_;*/

}

D3DXMATRIX* Camera::updateCamera() {

	pEye = transform_->position();
	pAt = *(transform_->forward());

	D3DXMatrixLookAtLH(&matView_,
		&pEye,    // the camera position
		&pAt,    // the look-at position
		&pUp);    // the up direction
	return &matView_;
}


int Camera::fov()
{
	return i_fov_;
}


void Camera::setFov(int newfov)
{
	i_fov_ = newfov;
}

float Camera::nearViewPlane()
{
	return i_nearViewPlane_;
}

void Camera::nearViewPlane(float newNearViewPlane)
{
	i_nearViewPlane_ = newNearViewPlane;
}

float Camera::farViewPlane()
{
	return i_farViewPlane_;
}

void Camera::farViewPlane(float newfarViewPlane)
{
	i_farViewPlane_ = newfarViewPlane;
}
