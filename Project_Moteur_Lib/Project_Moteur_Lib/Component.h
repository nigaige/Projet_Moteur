#pragma once

class AbstractComponent {
	bool comp = false;
};

template <class T>
class Component: public AbstractComponent
{
private:
	bool comp = true;
	bool active;
public:
	void setActive(bool a = true);


};

