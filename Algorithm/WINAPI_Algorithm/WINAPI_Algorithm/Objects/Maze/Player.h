#pragma once

class Maze;
class Block;

class Player
{
public:
	Player(shared_ptr<Maze> maze);
	~Player();

	void BeginPlay();

	void FindPath();
	bool Cango(int y, int x);

	void Update();

private:
	Vector2 _pos = {1,1};

	vector<Vector2> _path;
	int _pathIndex = 0;
	float  _time = 0.0f;

	shared_ptr<Maze> _maze;
};

