#include "pch.h"
#include "Block.h"

Block::Block()
: RectCollider(Vector2(), Vector2(5,5))
{
	_brushes.push_back(CreateSolidBrush(RGB(0,0,0)));
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
	SelectObject(hdc,_brushes[static_cast<int>(_type)]);
	RectCollider::Render(hdc);
}

void Block::SetPosition(Vector2 pos)
{
	_center = pos;
}

void Block::SetBlockType(BlockType type)
{
	switch (type)
	{
	case Block::BlockType::NONE:
	{
		_type = type;
	}
		break;
	case Block::BlockType::ABLE:
	{
		_type = type;
		SetGreen();
	}
		break;
	case Block::BlockType::DISABLE:
	{
		_type = type;
		SetRed();
	}
		break;
	default:
		break;
	}
}

