#pragma once
#include <Windows.h>

class Input
{
public:
	static char previousKey;

	static bool anyKeyDown();
	static bool getKeyDown(char* VK);
	static bool getKeyUp(char* VK);
	static bool getKeyDown(int VK);
	static bool getKeyUp(int VK);
};

