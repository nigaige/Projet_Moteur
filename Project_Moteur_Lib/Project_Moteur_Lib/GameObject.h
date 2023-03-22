#pragma once
#include "Component.h"
#include "Transform.h"
#include <vector>
#include "Utils.h"

class GameObject
{
private:
	//MAKE CUSTOMIZABLE?
	const static int maxComponent = 20;
	Transform* transform_;
	std::vector<Component*> componentList;
	int componentIndex = 0;
	bool toDisplay_;

public:
	GameObject();
	GameObject(Transform* T);


	Transform* transform()				{ return transform_; }
	void transform(Transform* trans)	{ transform_ = trans; }

	bool toDisplay()					{ return toDisplay_; }
	void toDisplay(bool display)		{ toDisplay_ = display; }


	 

	
	void addComponent(Component* comp);
	void rmComponent(Component* comp);
	Component* getComponent(int index);
	void rmComponent(int index);
	//void rmComponent(TYPE);

	int countComponent();

	template <typename T>
	T* findComponent();


	void Draw(){}
	bool collide(){}//Give another Collider
	


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
		/*
		Utils::DebugLogMessage(typeid(static_cast<T*>(comp)).name());
		Utils::DebugLogMessage(typeid(T).name());*/
		if (typeid(static_cast<T*>(comp)) == typeid(T*)) {
			return static_cast<T*>(comp);
		}
	}

	return nullptr;
}
