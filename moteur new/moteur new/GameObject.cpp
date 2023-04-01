#include "Utils.h"

GameObject::GameObject(){
	transform_ = new Transform(this);
	MeshlinkShader = std::map<Mesh*, Shader*>();
}

GameObject::GameObject(Transform* T)
{

	transform_ = T;
	transform_->gameObject(this);
}

GameObject::GameObject(Transform* T, GameObject* parent)
{
	transform_ = T;
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
	
	
	//remove manually the mesh without destroying them
	while (true) {
		if (rmComponent(findComponent<Mesh>())) continue;
		if (rmComponent(findComponent<Collider>())) continue;
		break;
	}

	delete transform_;

	parent_ = nullptr;

	rb_ = nullptr;


	for (Component* co : componentList)
		delete co;
	for (GameObject* chi : childList_) chi = nullptr;
	for (Collider* col : ColliderList) col = nullptr;
	ColliderList.clear();


	MeshList.clear();

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

Shader* GameObject::shaderFinder(Mesh* Mesh_)
{
	if (MeshlinkShader.size() == 0) return nullptr;
	return  MeshlinkShader.find(Mesh_)->second;
	
	
}

void GameObject::setShaderLinker(Mesh* Mesh_, Shader* Shader_)
{
	MeshlinkShader.insert(std::pair<Mesh*, Shader*>(Mesh_, Shader_));
}

void GameObject::addComponent(Component* comp)
{

	if (isOfType<Mesh>(comp)) {
		MeshList.push_back(castToType<Mesh>(comp));
	}
	else if (isOfType<Collider>(comp)){
		ColliderList.push_back(castToType<Collider>(comp));
	}else if (isOfType<RigidBody>(comp)) {
		if (rb_ != nullptr) return;
		rb_ = castToType<RigidBody>(comp);
	}

	comp->gameObject(this);
	comp->transform(transform_);
	
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
	return nullptr;
}

std::vector<Component*> GameObject::findAllComponent(ComponentType type)
{
	std::vector<Component*> list;

	for (Component* comp : componentList)
	{
		if (comp->type() == type) {
			list.push_back(comp);
		}
	}
	return list;
}
