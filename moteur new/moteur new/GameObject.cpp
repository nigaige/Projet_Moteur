#include "GameObject.h"

GameObject::GameObject(){
	transform_ = new Transform();
}

GameObject::GameObject(Transform* T)
{
	transform_ = T;
}

void GameObject::addComponent(Component* comp)
{
	componentList.push_back(comp);
	componentCount++;
}

void GameObject::rmComponent(Component* comp)
{
	for (int i = 0; i < componentCount; i++) {
		if (componentList[i] == comp) {
			componentList.erase(componentList.begin() + i, componentList.begin() + i + 1);
			componentCount--;
			return;
		}
	}
	throw "Component doesn't exis or belong to this Gameobject";

}

void GameObject::rmComponent(int index)
{
	delete componentList[index];
	componentList[index] = new Component;
	componentCount--;
}

Component* GameObject::getComponent(int index)
{
	return componentList[index];
}

int GameObject::countComponent()
{
	return componentCount;
}
