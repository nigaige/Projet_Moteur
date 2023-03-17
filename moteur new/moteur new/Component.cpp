#include "Component.h"

Component::Component(bool isActive, GameObject* go)
{
	active = isActive;
	gameobject = go;
}

Component::~Component()
{
}
