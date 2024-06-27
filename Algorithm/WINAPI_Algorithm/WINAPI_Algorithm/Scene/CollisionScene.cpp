#include "pch.h"
#include "CollisionScene.h"

CollisionScene::CollisionScene()
{
	_circle1 = make_shared<CircleCollider>(Vector2(500,500), 50);
	_circle2 = make_shared<CircleCollider>(Vector2(0,0), 30);
}

CollisionScene::~CollisionScene()
{
}

void CollisionScene::Update()
{
	// _circle2->_center = mousePos;

	_circle1->Update();
	_circle2->Update();

	if (_circle1->IsCollision(mousePos))
		_circle1->SetRed();
	else
		_circle1->SetGreen();
}

void CollisionScene::Render(HDC hdc)
{
	_circle1->Render(hdc);
	_circle2->Render(hdc);
}
