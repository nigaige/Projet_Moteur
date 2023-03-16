#pragma once
#include "Utils.h"
class GameObject
{
private:
	Transform* transform_;
	std::vector<Component*> componentList;
	bool toDisplay_ = false;
	int componentCount = 0;


public:
	GameObject();
	GameObject(Transform* T);

	//	GET/SET
	Transform* transform() { return transform_; }
	void transform(Transform* trans) { transform_ = trans; }

	bool toDisplay() { return toDisplay_; }
	void toDisplay(bool display) { toDisplay_ = display; }



	void addComponent(Component* comp);
	void rmComponent(Component* comp);
	void rmComponent(int index);

	Component* getComponent(int index);

	int countComponent();


	template <typename T>
	T* findComponent();
};

/*
Call with:
gameobject.findcomponent<type>()
*/
template<typename T>
inline T* GameObject::findComponent()
{
	for (Component* comp : componentList)
	{
		//TODO IMPROVE CASTING, null ptr
		if (typeid(static_cast<T*>(comp)) == typeid(T*)) {
			return static_cast<T*>(comp);
		}
	}

	return nullptr;
}