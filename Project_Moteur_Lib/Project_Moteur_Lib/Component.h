#pragma once

class AbstractComponent {
};

template <class T> //TODO FIX
class Component: public AbstractComponent
{
private:
	bool active;
public:
	void setActive(bool a = true);


};

