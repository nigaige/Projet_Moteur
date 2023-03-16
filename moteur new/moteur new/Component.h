#pragma once
class Component
{
private:
	bool active;
public:
	Component();
	void setActive(bool a = true) { active = a; };
};

