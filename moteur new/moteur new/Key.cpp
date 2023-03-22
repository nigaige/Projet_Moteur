#include "Key.h"

Key::Key(std::string* name_, int key_)
{
	lastStates = States::NOTPRESS;
	name = name_;
	key = key_;
}

