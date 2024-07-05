#include "pch.h"
#include "AlkanoidScene.h"

#include "Objects/Alkanoid/PlayerBar.h"
#include "Objects/Alkanoid/PlayerBall.h"

AlkanoidScene::AlkanoidScene()
{
	_playerBar= make_shared<PlayerBar>();
	_playerBall = make_shared<PlayerBall>();

	BeforeFireUpdate();
}

AlkanoidScene::~AlkanoidScene()
{
}


void AlkanoidScene::Update()
{
	BeforeFireUpdate();

	Fire();

	_playerBar->IsCollision(_playerBall);

	_playerBar->Update();
	_playerBall->Update();
}

void AlkanoidScene::Render(HDC hdc)
{
	_playerBar->Render(hdc);
	_playerBall->Render(hdc);
}

void AlkanoidScene::BeforeFireUpdate()
{
	if (_isFired == true) return;

	Vector2 pos = _playerBar->GetRectCollider()->_center;
	pos._y = _playerBar->GetRectCollider()->Top();
	pos._y -= _playerBall->GetCircleCollider()->_radius;

	_playerBall->SetPosition(pos);
}

void AlkanoidScene::Fire()
{
	if (_isFired == true) return;

	if (GetAsyncKeyState(VK_SPACE) & 0x0001)
	{
		_isFired = true;
		_playerBall->SetDir(Vector2(0, -1));
	}
}