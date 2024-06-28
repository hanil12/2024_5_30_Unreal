#include "pch.h"
#include "CollisionScene.h"

CollisionScene::CollisionScene()
{
	_circle1 = make_shared<CircleCollider>(Vector2(500,500), 50);
	_moveCircle = make_shared<CircleCollider>(Vector2(0,0), 30);

	_rect1 = make_shared<RectCollider>(Vector2(700,300), Vector2(50,70));
	_moveRect = make_shared<RectCollider>(Vector2(0,0), Vector2(30,30));
}

CollisionScene::~CollisionScene()
{
}

void CollisionScene::Update()
{
	// _circle2->_center = mousePos;
	_moveRect->_center = mousePos;

	_circle1->Update();
	_moveCircle->Update();

	_rect1->Update();
	_moveRect->Update();

	if (_circle1->IsCollision(_moveRect))
		_circle1->SetRed();
	else
		_circle1->SetGreen();

	if(_rect1->IsCollision(_moveRect))
		_rect1->SetRed();
	else
		_rect1->SetGreen();
}

void CollisionScene::Render(HDC hdc)
{
	_circle1->Render(hdc);
	_moveCircle->Render(hdc);
	_rect1->Render(hdc);
	_moveRect->Render(hdc);
}
