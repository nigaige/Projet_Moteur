#include "Utils.h"

GameObject::GameObject(){
	transform_ = new Transform(this);
}

GameObject::GameObject(Transform* T)
{
	*transform_ = *T;
	transform_->gameObject(this);
}

GameObject::GameObject(Transform* T, GameObject* parent)
{
	*transform_ = *T;
	transform_->gameObject(this);
	parent_ = parent;
	parent->addChild(this);
}

GameObject::GameObject(GameObject* parent)
{
	transform_ = new Transform(this);
	parent_ = parent;
	parent->addChild(this);
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

D3DXMATRIX* GameObject::updateTransform()
{
	return transform_->updateFinal(parent_);
}

void GameObject::setChildTransformToUpdate()
{
	int a = 0;
	if (childList_.size() == 0) return;
	for (GameObject* go : childList_) {
		go->transform()->toUpdate();
		go->setChildTransformToUpdate();
	}
}

D3DXMATRIX* GameObject::worldMatrix()
{
	return transform_->worldValue();
}

void GameObject::addChild(GameObject* go)
{
	//TODO make sure only one occurence
	childList_.push_back(go);
}

bool GameObject::rmChild(GameObject* go)
{
	for (int i = 0; i < childList_.size(); i++) {
		if (childList_[i] == go) {
			childList_.erase(childList_.begin() + i, childList_.begin() + i + 1);
			return true;
		}
	}
	return false;
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

Component* GameObject::findComponent(ComponentType type)
{
	for (Component* comp : componentList)
	{
		if (comp->type() == type) {
			return comp;
		}
	}
}
