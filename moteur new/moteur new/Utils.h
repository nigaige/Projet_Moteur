#pragma once

#include <windows.h>
#include <windowsx.h>
#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include <vector>

#include <d3d9.h>
#include <d3dx9.h>

#define CUSTOMFVF (D3DFVF_XYZ  | D3DFVF_DIFFUSE)
struct CUSTOMVERTEX { FLOAT X, Y, Z; DWORD COLOR; };

// define the screen resolution
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

#define DEGTORAD (M_PI / 180)
#define RADTODEG (180 / M_PI)

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


	static float DegToRad(float Angle);
	static float RadToDeg(float Rad);

};