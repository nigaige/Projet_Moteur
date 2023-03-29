#pragma once
#include "Utils.h"

class ObjectState : public BaseStates
{

protected:
	std::string name;
	void(*Enter_)();
	void(*Exit_)();
	void(*Update_)();

public:


	ObjectState() {};
	ObjectState(void(*Ent)(), void(*Ext)(), void(*Upd)()) {
		Enter_ = Ent;
		Exit_ = Ext;
		Update_ = Upd;
	};

	//GETTER / SETTER

	void SetEnterCallback(void(*Ent)())		{ Enter_ = Ent; }
	void SetExitCallback(void(*Ext)())		{ Exit_ = Ext; }
	void SetUpdateCallback(void(*Upd)())	{ Update_ = Upd; }
	void SetName(std::string newName)		{ name = newName; }
	void Enter();
	void Exit();
	void Update();

	~ObjectState() { };

};
