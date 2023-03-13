#pragma once

class AbstractComponent {

};

template <class T>
class Component: public AbstractComponent
{
	bool active;
	void setActive(bool a = true);


};

