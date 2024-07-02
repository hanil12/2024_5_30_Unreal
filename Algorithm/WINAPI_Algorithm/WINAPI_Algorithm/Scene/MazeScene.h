#pragma once
class MazeScene : public Scene
{
public:
	MazeScene();
	~MazeScene();

	void Update() override;
	void Render(HDC hdc) override;

private:
	shared_ptr<class Maze> _maze;
	shared_ptr<class Player> _mazeRunner;
};

