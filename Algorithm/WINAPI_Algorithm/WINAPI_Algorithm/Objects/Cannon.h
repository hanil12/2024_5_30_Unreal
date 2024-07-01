#pragma once
class Cannon
{
public:
	Cannon();
	~Cannon();

	void Update();
	void Render(HDC hdc);

	void Move();

private:
	shared_ptr<Collider> _body;
	shared_ptr<Line> _barrel;

	float _barrelLength = 100.0f;
	Vector2 _direction = Vector2(1,0);

	float _angle = 0.0f;
};

