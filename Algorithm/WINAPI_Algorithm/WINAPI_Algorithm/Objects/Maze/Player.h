#pragma once

class Maze;
class Block;

class Player
{
public:
	struct Vertex
	{
		bool operator<(const Vertex& other) const
		{
			if(g < other.g)	return true;
			return false;
		}

		bool operator>(const Vertex& other) const
		{
			if(g > other.g) return true;
			return false;
		}
		
		float g;
		Vector2 pos;
	};

	Player(shared_ptr<Maze> maze);
	~Player();

	void BeginPlay();

	// Find Path 알고리즘
	void RightHand();
	void DFS(Vector2 here);
	void BFS(Vector2 start);
	void Djikstra(Vector2 start);

	bool Cango(int y, int x);

	void Update();

private:
	Vector2 _pos = {1,1};

	vector<Vector2> _path;
	int _pathIndex = 0;
	float  _time = 0.0f;

	Vector2 _dir = Vector2(0,1);

	shared_ptr<Maze> _maze;

	// DFS
	vector<vector<bool>> _visited;

	// Djikstra

};

