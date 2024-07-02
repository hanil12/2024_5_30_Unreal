#pragma once
class Program
{
public:
	Program();
	~Program();

	void Update();
	// 그리기
	void Render(HDC hdc);

	static HDC backBuffer;
	// Buffer : 임시저장소 (곧 누군가에게 전달하거나, 전달받은 곳)
	// backBuffer : 화면에 노출되지는 않지만 임시적으로 그림을 그리는 곳

private:
	shared_ptr<class Scene> _scene;

	HBITMAP _hBitMap;
};

