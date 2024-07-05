#pragma once
class PlayerBar
{
public:
	PlayerBar();
	~PlayerBar();

	void Update();
	void Render(HDC hdc);

	void Input();

	shared_ptr<RectCollider> GetRectCollider() { return _rect; }

	void IsCollision(shared_ptr<class PlayerBall> ball);

private:
	float _speed = 5.0f;
	shared_ptr<RectCollider> _rect;
};

