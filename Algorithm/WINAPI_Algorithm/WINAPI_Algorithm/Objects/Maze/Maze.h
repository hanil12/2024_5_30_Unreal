#pragma once

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

private:
	vector<vector<shared_ptr<Block>>> _blocks;
};

