#pragma once
class Program
{
public:
	Program();
	~Program();

	void Update();
	// 그리기
	void Render(HDC hdc);

private:
	shared_ptr<class Scene> _scene;
};

