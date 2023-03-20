#include "Utils.h"

GameObject::GameObject(){
	transform_ = new Transform();
}

GameObject::GameObject(Transform* T)
{
	transform_ = T;
}

GameObject::~GameObject()
{
	//Mesh can be ref in other gameobject so we don't destroy them
	//TODO MATERIAL
	while (true) {
		if (rmComponent(findComponent<Mesh>())) continue;
		break;
	}
	Utils::DeleteVector(componentList);
	MeshList.clear();
	delete transform_;
}

void GameObject::update()
{
	for (Component* comp : componentList) {
		comp->update();
	}
}

void GameObject::addComponent(Component* comp)
{
	componentList.push_back(comp);

	if (isOfType<Mesh>(comp)) {
		MeshList.push_back(castToType<Mesh>(comp));
	}
}

bool GameObject::rmComponent(Component* comp)
{
	for (int i = 0; i < countComponent(); i++) {
		if (componentList[i] == comp) {
			componentList.erase(componentList.begin() + i, componentList.begin() + i + 1);
			return true;
		}
	}
	//NOTHING TO DELETE
	return false;

}

void GameObject::rmComponent(int index)
{
	//TODO RETURN BOOL
	componentList.erase(componentList.begin() + index, componentList.begin() + index + 1);
}

Component* GameObject::getComponent(int index)
{
	return componentList[index];
}

int GameObject::countComponent()
{
	return componentList.size();
}

std::vector<Mesh*> GameObject::meshToDraw()
{
	return MeshList;
}
