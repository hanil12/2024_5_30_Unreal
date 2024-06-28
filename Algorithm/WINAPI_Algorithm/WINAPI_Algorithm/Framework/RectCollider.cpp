#include "pch.h"
#include "RectCollider.h"

RectCollider::RectCollider(Vector2 center, Vector2 halfSize)
: Collider(center), _halfSize(halfSize)
{
	_type = ColliderType::RECT;
}

RectCollider::~RectCollider()
{
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

bool RectCollider::IsCollision(Vector2 point)
{
	// 포인트.x가 left,right 사이에 있냐?
	if (point._x < Right() && point._x > Left())
	{
		// 포인트.y가 bottom,top 사이에 있냐?
		if(point._y < Bottom() && point._y > Top())
			return true;
	}

	return false;
}

bool RectCollider::IsCollision(shared_ptr<CircleCollider> other)
{
	return other->IsCollision(shared_from_this());
}

bool RectCollider::IsCollision(shared_ptr<RectCollider> other)
{
	if (Right() > other->Left() && Left() < other->Right())
	{
		if(Bottom() > other->Top() && Top() < other->Bottom())
			return true;
	}

	return false;
}
