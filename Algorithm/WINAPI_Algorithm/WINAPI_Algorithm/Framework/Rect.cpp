#include "pch.h"
#include "Rect.h"

Rect::Rect(Vector2 center, Vector2 halfSize)
: _center(center), _halfSize(halfSize)
{
}

void Rect::Update()
{
}

void Rect::Render(HDC hdc)
{
	int left = _center._x - _halfSize._x;
	int right = _center._x + _halfSize._x;
	int top = _center._y - _halfSize._y;
	int bottom = _center._y + _halfSize._y;

	Rectangle(hdc,left,top,right,bottom);
}
