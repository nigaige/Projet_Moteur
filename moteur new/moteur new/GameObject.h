#pragma once


class GameObject
{
private:
	Transform* transform_;
	std::vector<Component*> componentList;
	bool toDisplay_ = false;
	std::vector<Mesh*> MeshList;


public:
	GameObject();
	GameObject(Transform* T);
	~GameObject();

	void update();

	//TODO DESTRUCTOR DELETE THE COMPONENT

	//	GET/SET
	Transform* transform() { return transform_; }
	void transform(Transform* trans) { transform_ = trans; }

	bool toDisplay() { return toDisplay_; }
	void toDisplay(bool display) { toDisplay_ = display; }



	void addComponent(Component* comp);
	bool rmComponent(Component* comp);
	void rmComponent(int index);

	Component* getComponent(int index);

	int countComponent();




	std::vector<Mesh*> meshToDraw();



	template <typename T>
	T* findComponent();
	template <typename T>
	bool isOfType(Component* comp);
	template <typename T>
	T* castToType(Component* comp);



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
		if (static_cast<T*>(comp) != nullptr) {
			return static_cast<T*>(comp);
		}
	}

	return nullptr;
}

template<typename T>
inline bool GameObject::isOfType(Component* comp) {

	T* a = static_cast<T*>(comp);
	return dynamic_cast<T*>(comp) != nullptr;	//TODO DYNAMIC...?
}

template<typename T>
inline T* GameObject::castToType(Component* comp)
{
	return static_cast<T*>(comp);
}
