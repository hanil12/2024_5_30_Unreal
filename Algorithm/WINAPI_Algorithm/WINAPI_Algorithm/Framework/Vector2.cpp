#include "pch.h"
#include "Vector2.h"

float Vector2::Length() const
{
	return sqrt(_x * _x + _y * _y);
}

float Vector2::Distance(Vector2 other) const
{
	Vector2 temp = other - *this;

	return temp.Length();
}

void Vector2::Normalize()
{
	_x = _x / Length();
	_y = _y / Length();
}

Vector2 Vector2::NormalVector2()
{
	Vector2 result = *this;
	result.Normalize();

	return result;
}
