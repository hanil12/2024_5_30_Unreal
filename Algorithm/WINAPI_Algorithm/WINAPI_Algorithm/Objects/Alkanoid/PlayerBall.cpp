#include "pch.h"
#include "PlayerBall.h"

PlayerBall::PlayerBall()
{
	_circle = make_shared<CircleCollider>(Vector2(-1000,0), 10.0f);
}

PlayerBall::~PlayerBall()
{
}

void PlayerBall::Update()
{
	Move();

	_circle->Update();

	// 상하좌우 반사
	if (_circle->_center._x < leftTop._x || _circle->_center._x > rightBottom._x)
	{
		_dir._x *= -1;
	}
	if (_circle->_center._y < leftTop._y || _circle->_center._y > rightBottom._y)
	{
		_dir._y *= -1;
	}
}

void PlayerBall::Render(HDC hdc)
{
	_circle->Render(hdc);
}

void PlayerBall::Move()
{
	_circle->_center += _dir * _speed;
}
