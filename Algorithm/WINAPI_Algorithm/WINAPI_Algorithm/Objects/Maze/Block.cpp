#include "pch.h"
#include "Block.h"

Block::Block()
: RectCollider(Vector2(), Vector2(5,5))
{
	_brushes.push_back(CreateSolidBrush(GREEN));
	_brushes.push_back(CreateSolidBrush(RED));
	SetGreen();
}

Block::~Block()
{
	for(auto brush : _brushes)
		DeleteObject(brush);
}

void Block::Update()
{
	RectCollider::Update();
}

void Block::Render(HDC hdc)
{
	SelectObject(hdc,_brushes[_curBrush]);
	RectCollider::Render(hdc);
}

void Block::SetPosition(Vector2 pos)
{
	_center = pos;
}

void Block::SetRed()
{
	Collider::SetRed();
	_curBrush = 1;
}

void Block::SetGreen()
{
	Collider::SetGreen();
	_curBrush = 0;
}
