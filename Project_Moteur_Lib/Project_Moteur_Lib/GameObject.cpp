#include "GameObject.h"

GameObject::GameObject()
{
	toDisplay = false;
}

GameObject::GameObject(Transform T)
{
	toDisplay = false;
	transform_ = &T;
}

void GameObject::addComponent(AbstractComponent* comp)
{
	componentList.push_back(comp);
}

void GameObject::rmComponent(AbstractComponent* comp)
{

	for (int i = 0; i < maxComponent; i++) {
		if (componentList[i] == comp) {
			componentList.erase(componentList.begin() + i, componentList.begin() + i + 1);
			return;
		}
	}
	throw "Component doesn't exis or belong to this Gameobject";
}

AbstractComponent* GameObject::getComponent(int index)
{
	return componentList[index];
}

void GameObject::rmComponent(int index)
{
	delete componentList[index];
	componentList[index] = new AbstractComponent;
}
