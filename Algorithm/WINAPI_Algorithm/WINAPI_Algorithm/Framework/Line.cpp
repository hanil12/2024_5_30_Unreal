#include "pch.h"
#include "Line.h"

Line::Line(Vector2 start, Vector2 end)
: _start(start), _end(end)
{
	_pens.push_back(CreatePen(PS_SOLID,3,RED));
	_pens.push_back(CreatePen(PS_SOLID,3,GREEN));

	SetGreen();
}

Line::~Line()
{
	for(auto pen : _pens)
		DeleteObject(pen);
}

void Line::Update()
{
}

void Line::Render(HDC hdc)
{
	SelectObject(hdc, _curPen);

	MoveToEx(hdc,_start._x, _start._y,nullptr);
	LineTo(hdc,_end._x,_end._y);
}

HResult Line::IsCollision(shared_ptr<Line> other)
{
	HResult result;
	result.isCollision = false;
	result.hitPoint = Vector2();

	Vector2 A1 = _end - _start;
	Vector2 A2 = other->_start - _start;
	Vector2 A3 = other->_end - _start;

	bool check1 = A1.IsBetween(A2, A3);

	Vector2 B1 = other->_end - other->_start;
	Vector2 B2 = _start - other->_start;
	Vector2 B3 = _end - other->_start;

	bool check2 = B1.IsBetween(B2,B3);

	result.isCollision = check1 && check2;

	if (result.isCollision)
	{
		float leftTriangle = abs(A1.Cross(A2));
		float rightTriangle = abs(A1.Cross(A3));

		float t = leftTriangle / (leftTriangle + rightTriangle);

		result.hitPoint = LERP(other->_start, other->_end, t);
	}

	return result;
}

