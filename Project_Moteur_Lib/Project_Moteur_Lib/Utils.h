#pragma once
#include <windows.h>
#include <windowsx.h>
#include <iostream>

#include <d3d9.h>
#include <d3dx9.h>

struct CUSTOMVERTEX { FLOAT X, Y, Z; DWORD COLOR; };


class Utils
{
public:
	static void DebugLogMessage(const char* message);
	static void DebugLogMessage(std::string* message);
	static void DebugLogMessage(int* message);
	static void DebugLogMessage(int message);
};