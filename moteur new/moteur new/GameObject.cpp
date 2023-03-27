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
	if (rb_ != nullptr) {
		rb_->update();
	}
	for (Component* comp : componentList) {
		if (comp->type() == RIGIDBODY)continue;
		comp->update();
	}
}

void GameObject::fixedUpdate()
{
	if (rb_ != nullptr) {
		rb_->fixedUpdate();
	}
	for (Component* comp : componentList) {
		if (comp->type() == RIGIDBODY)continue;
		comp->fixedUpdate();
	}
}

void GameObject::addComponent(Component* comp)
{

	if (isOfType<Mesh>(comp)) {
		MeshList.push_back(castToType<Mesh>(comp));
	}
	else {
		if (isOfType<Collider>(comp)) {
			ColliderList.push_back(castToType<Collider>(comp));
		}
		else if (isOfType<RigidBody>(comp)) {
			if (rb_ != nullptr) return;
			rb_ = castToType<RigidBody>(comp);
		}
		comp->gameObject(this);
		comp->transform(transform_);
	}
	componentList.push_back(comp);
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

bool GameObject::rmComponent(int index)
{
	if (index < 0 || index >= componentList.size()) return false;
	componentList.erase(componentList.begin() + index, componentList.begin() + index + 1);
	return true;
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

Component* GameObject::findComponent(ComponentType type)
{
	for (Component* comp : componentList)
	{
		if (comp->type() == type) {
			return comp;
		}
	}
}
