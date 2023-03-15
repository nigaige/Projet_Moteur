#pragma once

class AbstractComponent {
};

class Component: public AbstractComponent
{
private:
	bool active;
public:
	void setActive(bool a = true);

};

