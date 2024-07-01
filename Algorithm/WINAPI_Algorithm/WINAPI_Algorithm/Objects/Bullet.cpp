#include "pch.h"
#include "Bullet.h"

Bullet::Bullet()
{
	_col = make_shared<CircleCollider>(CENTER, 7);
}

Bullet::~Bullet()
{
}

void Bullet::Update()
{
	if(_isActive == false) return;

	_col->Update();
	_col->_center += _direction * _speed;

	_col->_center += _downVector;
	_downVector += Vector2(0, 1) * GRAVITY;
}

void Bullet::Render(HDC hdc)
{
	if(_isActive == false) return;

	_col->Render(hdc);
}

void Bullet::Fire(Vector2 startPos, Vector2 direction)
{
	_isActive = true;
	_col->_center = startPos;
	_direction = direction;
	_direction.Normalize();
	_downVector = Vector2();
}

void Bullet::SetActive(bool isActive)
{
	_downVector = Vector2();
	_isActive = isActive;
}
