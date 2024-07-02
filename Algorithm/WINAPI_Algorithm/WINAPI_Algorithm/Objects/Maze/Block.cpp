#include "pch.h"
#include "Block.h"

Block::Block()
: RectCollider(Vector2(), Vector2(5,5))
{
	_brushes.push_back(CreateSolidBrush(RGB(0,0,0)));
	_brushes.push_back(CreateSolidBrush(GREEN));
	_brushes.push_back(CreateSolidBrush(RED));
	_brushes.push_back(CreateSolidBrush(SKYCOLOR));
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
	SelectObject(hdc,_brushes[static_cast<int>(_type)]);
	RectCollider::Render(hdc);
}

void Block::SetPosition(Vector2 pos)
{
	_center = pos;
}

void Block::SetBlockType(BlockType type)
{
	_type = type;

	switch (type)
	{
	case Block::BlockType::NONE:
	{
	}
		break;
	case Block::BlockType::ABLE:
	{
		SetGreen();
	}
		break;
	case Block::BlockType::DISABLE:
	{
		SetRed();
	}
		break;
	default:
		break;
	}
}

