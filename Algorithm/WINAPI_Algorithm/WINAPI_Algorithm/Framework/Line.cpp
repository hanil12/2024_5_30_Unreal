#include "pch.h"
#include "Line.h"

Line::Line(Vector2 start, Vector2 end)
: _start(start), _end(end)
{
}

Line::~Line()
{
}

void Line::Update()
{
}

void Line::Render(HDC hdc)
{
	MoveToEx(hdc,_start._x, _start._y,nullptr);
	LineTo(hdc,_end._x,_end._y);
}
