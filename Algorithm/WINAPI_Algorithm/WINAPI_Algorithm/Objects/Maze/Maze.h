#pragma once

#include "Block.h"

class Block;

#define MAXCOUNT_X 25
#define MAXCOUNT_Y 25

class Maze
{
public:
	Maze();
	~Maze();

	void Update();
	void Render(HDC hdc);

	void CreateMaze();
	Block::BlockType GetBlockType(int y, int x);

	void SetPlayerPos(Vector2 pos);

private:
	vector<vector<shared_ptr<Block>>> _blocks;
};

