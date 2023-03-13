#pragma once
#include "Component.h"
#include "Transform.h"



class GameObject
{
private:
	//MAKE CUSTOMIZABLE?
	const static int maxComponent = 20;
	Transform transform_;
	AbstractComponent* componentList[maxComponent];

public:
	Transform transform()			{ return transform_; }
	void transform(Transform trans) { transform_ = trans; }
	
	void addComponent(AbstractComponent* comp);
	void rmComponent(AbstractComponent* comp);
	void rmComponent(int index);
	//void rmComponent(TYPE);
	//void findComponent(TYPE);
	


};

