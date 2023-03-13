#include "GameObject.h"

void GameObject::addComponent(AbstractComponent* comp)
{
	componentList[componentIndex] = comp;
	componentIndex++;
}

void GameObject::rmComponent(AbstractComponent* comp)
{
	delete componentList[componentIndex];
	componentList[componentIndex] = new AbstractComponent;

}

void GameObject::rmComponent(int index)
{
}
