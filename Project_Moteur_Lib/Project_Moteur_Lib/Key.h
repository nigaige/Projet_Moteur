#pragma once
#include <string>

class Key
{
private:

	enum States
	{
		NOTPRESS,
		HOLD,
		PRESSED,
		RELEASED
	};

	std::string* name;
	int* key;
	States* lastStates;

public :
	Key(std::string* name, int* key){};

};

