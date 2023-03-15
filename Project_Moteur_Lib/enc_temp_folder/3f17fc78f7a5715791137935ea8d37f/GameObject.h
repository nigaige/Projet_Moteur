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

public:
	Transform* transform()			{ return transform_; }
	void transform(Transform* trans) { transform_ = trans; }
	
	void addComponent(AbstractComponent* comp);
	void rmComponent(AbstractComponent* comp);
	void rmComponent(int index);
	//void rmComponent(TYPE);
	//void findComponent(TYPE);


	void Draw(){}
	bool collide(){}//Give another Collider
	


};

