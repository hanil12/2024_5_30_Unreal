#include "pch.h"
#include "MazeScene.h"

#include "Objects/Maze/Maze.h"
#include "Objects/Maze/Player.h"

MazeScene::MazeScene()
{
	_maze = make_shared<Maze>();
	_mazeRunner = make_shared<Player>(_maze);

	_mazeRunner->BeginPlay();
}

MazeScene::~MazeScene()
{
}

void MazeScene::Update()
{
	_maze->Update();
	_mazeRunner->Update();
}

void MazeScene::Render(HDC hdc)
{
	wstring temp = L"Hello Maze!!!";
	TextOut(hdc, CENTER._x - 100, 100, temp.c_str(),temp.size());

	_maze->Render(hdc);
}
