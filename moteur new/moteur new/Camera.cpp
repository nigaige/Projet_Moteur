#pragma once
#include "Utils.h"

Camera::Camera(int Fov, int nearVIewPlane, int farViewPlane){


	pEye = D3DXVECTOR3(0.0f, 0.0f, 20.0f);
	pAt  = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pUp  = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	i_fov_ = Fov;
	i_nearViewPlane_ = nearVIewPlane;
	i_farViewPlane_ = farViewPlane;
}


Camera::~Camera(){

}

void Camera::updateCamera() {

	pEye = transform()->position();
	pAt = transform()->forward();

	D3DXMatrixLookAtLH(&matView,
		&pEye,    // the camera position
		&pAt,    // the look-at position
		&pUp);    // the up direction
}

D3DXMATRIX* Camera::getMatView()
{
	return &matView;
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
	return i_fov_;
}

void Camera::setNearViewPlane(int newNearViewPlane)
{
	i_nearViewPlane_ = newNearViewPlane;
}

float Camera::farViewPlane()
{
	return i_fov_;
}

void Camera::setFarViewPlane(int newfarViewPlane)
{
	i_farViewPlane_ = newfarViewPlane;
}
