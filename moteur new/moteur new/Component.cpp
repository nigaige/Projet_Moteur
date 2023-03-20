#pragma once
#include "Utils.h"

Component::Component(bool isActive, GameObject* go)
{
	active = isActive;
	gameobject = go;
}


Component::~Component()
{
}
