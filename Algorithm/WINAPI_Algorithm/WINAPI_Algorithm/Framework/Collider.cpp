#include "pch.h"
#include "Collider.h"

Collider::Collider(Vector2 center)
: _center(center)
{
	_pens.push_back(CreatePen(PS_SOLID, 3, GREEN));
	_pens.push_back(CreatePen(PS_SOLID, 3, RED));

	SetColor(GREEN_COLOR);
}

Collider::~Collider()
{
	for (auto pen : _pens)
		DeleteObject(pen);
}

bool Collider::IsCollision(shared_ptr<Collider> col)
{
	switch (col->_type)
	{
	case ColliderType::NONE:
	{
		return false;
	}
	
	case ColliderType::RECT:
	{
		auto rect = dynamic_pointer_cast<RectCollider>(col);
		return IsCollision(rect);
	}
	case ColliderType::CIRCLE:
	{
		auto circle = dynamic_pointer_cast<CircleCollider>(col);
		return IsCollision(circle);
	}

	default:
		break;
	}

	return false;
}

void Collider::SetColor(ColorNum num)
{
	_curPen = _pens[num];
}
