#include "GameObject.h"

GameObject::GameObject()
{
	toDisplay_ = false;
}

GameObject::GameObject(Transform* T)
{
	toDisplay_ = false;
	transform_ = T;
}



void GameObject::addComponent(Component* comp)
{
	componentList.push_back(comp);
	
}

void GameObject::rmComponent(Component* comp)
{

	for (int i = 0; i < maxComponent; i++) {
		if (componentList[i] == comp) {
			componentList.erase(componentList.begin() + i, componentList.begin() + i + 1);
			return;
		}
	}
	throw "Component doesn't exis or belong to this Gameobject";
}

Component* GameObject::getComponent(int index)
{
	return componentList[index];
}

void GameObject::rmComponent(int index)
{
	delete componentList[index];
	componentList[index] = new Component;
}

int GameObject::countComponent()
{
	return componentList.size();
}

