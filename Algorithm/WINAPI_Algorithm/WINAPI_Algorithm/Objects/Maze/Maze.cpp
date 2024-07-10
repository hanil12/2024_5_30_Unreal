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
			block->SetBlockType(Block::BlockType::DISABLE);
			block->SetPosition(blockOffset);
			blocks_X.push_back(block);
		}

		_blocks.push_back(blocks_X);
	}

	CreateMaze_Kruskal();
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
	// 프로그래머를 위한 미로만들기
	// 갈 수 있는 노드들을 만들기
	for (int y = 0; y < MAXCOUNT_Y; y++)
	{
		for (int x = 0; x < MAXCOUNT_X; x++)
		{
			if (x % 2 == 0 || y % 2 == 0)
			{
				_blocks[y][x]->SetBlockType(Block::BlockType::DISABLE);
			}
			else
			{
				_blocks[y][x]->SetBlockType(Block::BlockType::ABLE);
			}
		}
	}

	for (int y = 0; y < MAXCOUNT_Y; y++)
	{
		for (int x = 0; x < MAXCOUNT_X; x++)
		{
			if (x == 1 && y == 1) // 시작점
			{
				_blocks[y][x]->SetBlockType(Block::BlockType::ABLE);
			}

			if (x == MAXCOUNT_X - 2 && y == MAXCOUNT_Y - 2) // 끝점
			{
				_blocks[y][x]->SetBlockType(Block::BlockType::ABLE);
				continue;
			}

			if (x % 2 == 0 || y % 2 == 0)
				continue;

			if (x == MAXCOUNT_X - 2)
			{
				_blocks[y + 1][x]->SetBlockType(Block::BlockType::ABLE);
				continue;
			}

			if (y == MAXCOUNT_Y - 2)
			{
				_blocks[y][x + 1]->SetBlockType(Block::BlockType::ABLE);
				continue;
			}

			// 난수를 이용하여 오른쪽 혹은 아래 쪽 선택해서 뚫기
			int randValue = rand() % 2;
			if(randValue == 0)
				_blocks[y][x + 1]->SetBlockType(Block::BlockType::ABLE);
			else
				_blocks[y+1][x]->SetBlockType(Block::BlockType::ABLE);
		}
	}
}

void Maze::CreateMaze_Kruskal()
{
	for (int y = 0; y < MAXCOUNT_Y; y++)
	{
		for (int x = 0; x < MAXCOUNT_X; x++)
		{
			if (x % 2 == 0 || y % 2 == 0)
			{
				_blocks[y][x]->SetBlockType(Block::BlockType::DISABLE);
			}
			else
			{
				_blocks[y][x]->SetBlockType(Block::BlockType::ABLE);
			}
		}
	}

	// Edge를 만드는 작업
	vector<Edge> edges;
	for (int y = 0; y < MAXCOUNT_Y; y++)
	{
		for (int x = 0; x < MAXCOUNT_X; x++)
		{
			if (x % 2 == 0 || y % 2 == 0)
				continue;

			if (x < MAXCOUNT_X - 2)
			{
				int randCost = rand() % 100;

				Edge edge;
				edge.cost = randCost;
				edge.u = Vector2(y,x);
				edge.v = Vector2 (y, x + 2);

				edges.push_back(edge);
			}

			if (y < MAXCOUNT_Y - 2)
			{
				int randCost = rand() % 100;

				Edge edge;
				edge.cost = randCost;
				edge.u = Vector2(y,x);
				edge.v = Vector2(y + 2, x);

				edges.push_back(edge);
			}
		}
	}

	// Sort
	std::sort(edges.begin(), edges.end(), [](const Edge& e1, const Edge& e2)->bool 
	{
		if(e1.cost < e2.cost)
			return true;
		return false;
	});

	DisJointSet set(MAXCOUNT_X * MAXCOUNT_Y);

	for (auto& edge : edges)
	{
		// Vector2(x,y) = (y,x)
		int u = edge.u._y + edge.u._x * MAXCOUNT_X;
		int v = edge.v._y + edge.v._x * MAXCOUNT_X;

		if(set.FindLeader(u) == set.FindLeader(v))
			continue;

		set.Merge(u,v);
		
		int x = ((int)edge.u._y + (int)edge.v._y) / 2;
		int y = ((int)edge.u._x + (int)edge.v._x) / 2;

		_blocks[y][x]->SetBlockType(Block::BlockType::ABLE);
	}
}

Block::BlockType Maze::GetBlockType(int y, int x)
{
	return _blocks[y][x]->GetBlockType();
}

void Maze::SetBlockType(int y, int x, Block::BlockType type)
{
	_blocks[y][x]->SetBlockType(type);
}

void Maze::SetPlayerPos(Vector2 pos)
{
	_blocks[pos._y][pos._x]->SetBlockType(Block::BlockType::PLAYER_POS);
}
