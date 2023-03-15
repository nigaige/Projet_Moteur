#pragma once
#include <windows.h>
#include <windowsx.h>
#include <iostream>

class Utils
{
public:
	static void DebugLogMessage(const char* message);
	static void DebugLogMessage(std::string* message);
	static void DebugLogMessage(int* message);
	static void DebugLogMessage(int message);
};