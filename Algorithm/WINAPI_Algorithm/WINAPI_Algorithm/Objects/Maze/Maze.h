#pragma once

#include "Block.h"

class Block;

#define MAXCOUNT_X 25
#define MAXCOUNT_Y 25

class Maze
{
public:
	struct Edge
	{
		Vector2 u;
		Vector2 v;

		int cost = 0;
	};

	Maze();
	~Maze();

	void Update();
	void Render(HDC hdc);

	void CreateMaze();
	void CreateMaze_Kruskal();

	Block::BlockType GetBlockType(int y, int x);
	void SetBlockType(int y, int x, Block::BlockType type);

	void SetPlayerPos(Vector2 pos);

	Vector2 GetStartPos() { return Vector2(1,1); }
	Vector2 GetEndPos() { return Vector2(MAXCOUNT_Y- 2, MAXCOUNT_X - 2); }

private:
	vector<vector<shared_ptr<Block>>> _blocks;
};

