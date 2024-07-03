#pragma once

class Vector2
{
public:
	Vector2() { _x = 0; _y = 0; }
	Vector2(float x, float y) { _x = x; _y = y; }
	~Vector2() {}

	Vector2 operator+(const Vector2& other)
	{
		Vector2 result;
		result._x = this->_x + other._x;
		result._y = _y + other._y;

		return result;
	}

	Vector2 operator-(const Vector2& other)
	{
		Vector2 result;
		result._x = this->_x - other._x;
		result._y = _y - other._y;

		return result;
	}

	Vector2 operator*(float value)
	{
		Vector2 result;
		result._x = _x * value;
		result._y = _y * value;

		return result;
	}

	Vector2 operator/(float value)
	{
		Vector2 result;
		result._x = _x / value;
		result._y = _y / value;

		return result;
	}

	Vector2& operator=(const Vector2& other)
	{
		this->_x = other._x;
		this->_y = other._y;

		return (*this);
	}

	Vector2& operator+=(const Vector2& other)
	{
		this->_x += other._x;
		this->_y += other._y;

		return (*this);
	}

	Vector2& operator-=(const Vector2& other)
	{
		this->_x -= other._x;
		this->_y -= other._y;

		return (*this);
	}

	Vector2 operator++(int)
	{
		Vector2 result = *this;
		*this = (*this) + Vector2(1, 1);

		return result;
	}

	Vector2& operator++()
	{
		(*this)++;
		return (*this);
	}

	float Dot(const Vector2& other)
	{
		float result = 0.0f;
		result = _x * other._x + _y * other._y;
		return result;
	}

	float Cross(const Vector2& other)
	{
		float result = _x * other._y - _y * other._x;
		return result;
	}

	bool operator==(const Vector2& other);
	bool operator!=(const Vector2& other);

	float Length() const;
	float Distance(Vector2 other) const;
	float Angle() const;

	void Normalize();

	Vector2 NormalVector2();

	bool IsBetween(Vector2 v1, Vector2 v2);

	float _x;
	float _y;
};