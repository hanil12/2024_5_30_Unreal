#include "pch.h"
#include "Maze.h"

#include "Block.h"

Maze::Maze()
{
	Vector2 offSet = Vector2(500,200);

	_blocks.reserve(MAXCOUNT_Y);

	for (int i = 0; i < MAXCOUNT_Y; i++)
	{
		vector<shared_ptr<Block>> blocks_X;
		blocks_X.reserve(MAXCOUNT_X);

		for (int j = 0; j < MAXCOUNT_X; j++)
		{
			Vector2 blockOffset = offSet + Vector2(16.0f * j, 16.0f * i);

			shared_ptr<Block> block = make_shared<Block>();
			block->SetPosition(blockOffset);
			blocks_X.push_back(block);
		}

		_blocks.push_back(blocks_X);
	}

	CreateMaze();
}

Maze::~Maze()
{
}

void Maze::Update()
{
	for (auto blocks_X : _blocks)
	{
		for (auto block : blocks_X)
		{
			block->Update();
		}
	}
}

void Maze::Render(HDC hdc)
{
	for (auto blocks_X : _blocks)
	{
		for (auto block : blocks_X)
		{
			block->Render(hdc);
		}
	}
}

void Maze::CreateMaze()
{

}
