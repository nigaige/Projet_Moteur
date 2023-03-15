#pragma once
#include "Component.h"
#include "Transform.h"
#include <vector>


class GameObject
{
private:
	//MAKE CUSTOMIZABLE?
	const static int maxComponent = 20;
	Transform* transform_;
	std::vector<AbstractComponent*> componentList;
	int componentIndex = 0;
	bool toDisplay_;

public:
	GameObject();
	GameObject(Transform* T);


	Transform* transform()				{ return transform_; }
	void transform(Transform* trans)	{ transform_ = trans; }

	bool toDisplay()					{ return toDisplay_; }
	void toDisplay(bool display)		{ toDisplay_ = display; }


	 

	
	void addComponent(AbstractComponent* comp);
	void rmComponent(AbstractComponent* comp);
	AbstractComponent* getComponent(int index);
	void rmComponent(int index);
	//void rmComponent(TYPE);

	template <typename T>
	T* findComponent();


	void Draw(){}
	bool collide(){}//Give another Collider
	


};

