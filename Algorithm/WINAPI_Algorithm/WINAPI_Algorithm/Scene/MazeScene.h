#pragma once
class MazeScene : public Scene
{
public:
	MazeScene();
	~MazeScene();

	void Update() override;
	void Render(HDC hdc) override;

private:

};

