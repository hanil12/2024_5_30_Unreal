#pragma once
class PlayerBall
{
public:
	PlayerBall();
	~PlayerBall();

	void Update();
	void Render(HDC hdc);

	void SetPosition(Vector2 pos) { _circle->_center = pos; }
	void SetDir(Vector2 dir) { _dir = dir; }
	Vector2 GetDir() { return _dir; }

	void Move();

	shared_ptr<CircleCollider> GetCircleCollider() { return _circle; }

private:
	Vector2 leftTop = {0,0};
	Vector2 rightBottom = {WIN_WIDTH, WIN_HEIGHT};

	bool _isFired = false;

	float _speed = 10.0f;
	Vector2 _dir = Vector2(0,0);

	shared_ptr<CircleCollider> _circle;
};

