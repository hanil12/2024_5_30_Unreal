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
	float length = Length();
	_x = _x / length;
	_y = _y / length;
}

Vector2 Vector2::NormalVector2()
{
	Vector2 result = *this;
	result.Normalize();

	return result;
}

bool Vector2::IsBetween(Vector2 v1, Vector2 v2)
{
	float Cross1 = this->Cross(v1); // +
	float Cross2 = this->Cross(v2); // -

	bool result = (Cross1 * Cross2) < 0;

	return result;
}
