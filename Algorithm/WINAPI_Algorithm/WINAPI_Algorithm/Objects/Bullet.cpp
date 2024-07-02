#include "pch.h"
#include "Bullet.h"
#include "Cannon.h"

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

	Attack_Cannon();

	_col->Update();
	_col->_center += _direction * _speed;

	// TODO(과제) : 중력 적용
	//_col->_center += _downVector;
	//_downVector += Vector2(0, 1) * GRAVITY;

	// TODO(과제) : 화면 밖으로 나갔을 시 사라지는 코드
	// OutControll : 반사를 위한 함수
	//bool isOut = IsOut();
	OutControll();
	bool isOut = false;
	if (_lifeTime > _delayTime || isOut)
	{
		_lifeTime = 0.0f;
		_isActive = false;
	}

	_lifeTime += 0.01f;
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

bool Bullet::IsOut()
{
	if(_col->_center._x > WIN_WIDTH || _col->_center._x < 0)
		return true;

	if(_col->_center._y > WIN_HEIGHT || _col->_center._y < 0)
		return true;

	return false;
}

void Bullet::OutControll()
{
	Vector2 center = _col->_center;
	// 화면 좌우로 나갔냐?
	if (center._x > WIN_WIDTH || center._x < 0)
	{
		_direction._x *= -1.0f;
	}

	if (center._y > WIN_HEIGHT || center._y < 0)
	{
		_direction._y *= -1.0f;
	}
}

void Bullet::Attack_Cannon(shared_ptr<Cannon> cannon)
{
	if(IsActive() == false)
		return;

	// cannon을 어떻게 공격할 것인가
	// => cannon의 body
	if (cannon->GetCollider()->IsCollision(_col))
	{
		SetActive(false);
	}
}

void Bullet::Attack_Cannon()
{
	if (_target.expired() == false)
	{
		shared_ptr<Cannon> targetCannon = _target.lock();
		shared_ptr<Collider> targetCannonCol = targetCannon->GetCollider();
		if (targetCannonCol->IsCollision(_col))
		{
			SetActive(false);
		}
	}
}
