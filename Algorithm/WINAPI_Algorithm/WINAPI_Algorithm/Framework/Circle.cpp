#include "pch.h"
#include "Circle.h"

CircleCollider::CircleCollider(Vector2 center, float radius)
: _center(center), _radius(radius)
{
	_pens.push_back(CreatePen(PS_SOLID, 3, GREEN));
	_pens.push_back(CreatePen(PS_SOLID, 3, RED));

	SetColor(GREEN_COLOR);
}

CircleCollider::~CircleCollider()
{
	for (auto pen : _pens)
		DeleteObject(pen);
}

void CircleCollider::Update()
{
}

void CircleCollider::Render(HDC hdc)
{
	SelectObject(hdc, _curPen);

	int left = _center._x - _radius;
	int top = _center._y - _radius;
	int right = _center._x + _radius;
	int bottom = _center._y + _radius;

	Ellipse(hdc,left,top,right,bottom);
}

bool CircleCollider::IsCollision(Vector2 point)
{
	float distance = _center.Distance(point);

	return distance < _radius;
}

bool CircleCollider::IsCollision(shared_ptr<CircleCollider> other)
{
	float distance = _center.Distance(other->_center);

	return distance < _radius + other->_radius;
}

bool CircleCollider::IsCollision(shared_ptr<RectCollider> other)
{
	// 과제
	// AABB(회전하지 않는다는 조건), OBB(회전이 가능하다)

	return false;
}

void CircleCollider::SetColor(ColorNum num)
{
	_curPen = _pens[num];
}
