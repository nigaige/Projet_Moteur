#include "Utils.h"



Component::Component(bool isActive)
{
	active = isActive;
}


Component::~Component()
{
	gameobject_ = nullptr;
	transform_ = nullptr;
	
}

void Component::gameObject(GameObject* go)
{
	transform_ = go->transform();
	gameobject_ = go;

}

GameObject* Component::gameObject()
{
	return gameobject_;
}

void Component::transform(Transform* trans)
{
	transform_ = trans;
}

