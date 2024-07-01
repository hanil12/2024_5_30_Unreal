#include "pch.h"
#include "Cannon.h"

Cannon::Cannon()
{
	_body = make_shared<CircleCollider>(CENTER, 50.0f);
	Vector2 barrelStart = _body->_center;
	Vector2 barrelEnd = Vector2(barrelStart._x + _barrelLength, barrelStart._y);
	_barrel = make_shared<Line>(barrelStart, barrelEnd);
}

Cannon::~Cannon()
{
}

void Cannon::Update()
{
	Move();

	_body->Update();
	_barrel->Update();
}

void Cannon::Render(HDC hdc)
{
	_barrel->Render(hdc);
	_body->Render(hdc);
}

void Cannon::Move()
{
	if (GetAsyncKeyState(VK_RIGHT))
	{
		_body->_center._x += 1.0f;
	}
	if (GetAsyncKeyState(VK_LEFT))
	{
		_body->_center._x -= 1.0f;
	}
	if (GetAsyncKeyState(VK_UP))
	{
		_angle -= 0.01f;
	}
	if (GetAsyncKeyState(VK_DOWN))
	{
		_angle += 0.01f;
	}

	//_direction._x =?
	//_direction._y =?

	Vector2 barrelStart = _body->_center;
	Vector2 barrelEnd = _body->_center + _direction * _barrelLength;
	_barrel->_start = barrelStart;
	_barrel->_end = barrelEnd;
}
