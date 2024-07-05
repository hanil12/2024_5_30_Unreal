#include "pch.h"
#include "PlayerBar.h"

#include "PlayerBall.h"

PlayerBar::PlayerBar()
{
	Vector2 temp = CENTER;
	temp._y += 200.0f;
	_rect =make_shared<RectCollider>(temp, Vector2(100,15));
}

PlayerBar::~PlayerBar()
{
}

void PlayerBar::Update()
{
	Input();

	_rect->Update();
}

void PlayerBar::Render(HDC hdc)
{
	_rect->Render(hdc);
}

void PlayerBar::Input()
{
	if (GetAsyncKeyState(VK_RIGHT))
	{
		_rect->_center._x += 1.0f * _speed;
	}
	if (GetAsyncKeyState(VK_LEFT))
	{
		_rect->_center._x -= 1.0f * _speed;
	}
}

void PlayerBar::IsCollision(shared_ptr<class PlayerBall> ball)
{
	if (ball->GetDir().Length() <= 0.001f)
	{
		return;
	}

	if(_rect->IsCollision(ball->GetCircleCollider()) == false)
		return;

	Vector2 cirPos = ball->GetCircleCollider()->_center;
	Vector2 rectPos = _rect->_center;

	Vector2 dir = cirPos - rectPos;
	dir.Normalize();

	ball->SetDir(dir);
}
