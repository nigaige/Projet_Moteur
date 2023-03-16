#pragma once

#include <windows.h>
#include <windowsx.h>
#include <iostream>
#include <vector>

#include <d3d9.h>
#include <d3dx9.h>

#define CUSTOMFVF (D3DFVF_XYZ  | D3DFVF_DIFFUSE)
struct CUSTOMVERTEX { FLOAT X, Y, Z; DWORD COLOR; };

// define the screen resolution
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600


class Component;
class Mesh;
class Moteur;
class GameObject;
class Transform;

#include "Component.h"
#include "Mesh.h"
#include "Moteur.h"
#include "GameObject.h"
#include "Transform.h"



// include the Direct3D Library files
#pragma comment (lib, "d3d9.lib")
#pragma comment (lib, "d3dx9.lib")

class Utils
{
public:
	static void DebugLogMessage(const char* message);
	static void DebugLogMessage(std::string* message);
	static void DebugLogMessage(int* message);
	static void DebugLogMessage(int message);
};