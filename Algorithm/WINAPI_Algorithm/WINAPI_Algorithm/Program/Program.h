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
	float _left = 0;
	float _top = 0; 
	float _right = 50;
	float _bottom = 50;
};

