#pragma once
#include "Framework/Vector2.h"

#define PI 3.141592f
#define GRAVITY 0.098f

#define WIN_WIDTH		1280
#define WIN_HEIGHT		720
#define CENTER			Vector2(WIN_WIDTH * 0.5f, WIN_HEIGHT * 0.5f)

#define RED				RGB(255,0,0)
#define GREEN			RGB(0,255,0)
#define BLUE			RGB(0,0,255)

#define PANTON			RGB(255,103,32)
#define SKYCOLOR		RGB(123,123,255)
#define INDIGO			RGB(75,0,130)

#define LERP(s,e,t)		s + (e - s) * t

struct HResult
{
	bool isCollision;
	class Vector2 hitPoint;
};