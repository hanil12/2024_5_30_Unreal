#include "pch.h"
#include "Rect.h"

#define GREEN_COLOR		0
#define RED_COLOR		1

RectCollider::RectCollider(Vector2 center, Vector2 halfSize)
: _center(center), _halfSize(halfSize)
{
	_pens.push_back(CreatePen(PS_SOLID,3,GREEN));
	_pens.push_back(CreatePen(PS_SOLID,3,RED));

	SetColor(GREEN_COLOR);
}

RectCollider::~RectCollider()
{
	for(auto pen : _pens)
		DeleteObject(pen);
}

void RectCollider::Update()
{
}

void RectCollider::Render(HDC hdc)
{
	SelectObject(hdc, _curPen);

	int left = _center._x - _halfSize._x;
	int right = _center._x + _halfSize._x;
	int top = _center._y - _halfSize._y;
	int bottom = _center._y + _halfSize._y;

	Rectangle(hdc,left,top,right,bottom);
}

void RectCollider::SetColor(ColorNum num)
{
	_curPen = _pens[num];
}
