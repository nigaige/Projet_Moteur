#pragma once
#include "Utils.h"
class Component
{
protected:
	bool active = false;
	
	GameObject* gameobject = nullptr;
public:
	//TODO GAMEOBJECT OWNER
	Component(bool isActive = true, GameObject* go = nullptr);
	~Component();
	void setActive(bool a = true) { active = a; };
	virtual void update() {};
};

