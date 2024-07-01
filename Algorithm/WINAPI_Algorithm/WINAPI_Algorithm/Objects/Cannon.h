#pragma once
class Cannon
{
public:
	Cannon();
	~Cannon();

	void Update();
	void Render(HDC hdc);

	void Move();
	void Fire();

private:
	shared_ptr<Collider> _body;
	shared_ptr<class Barrel> _barrel;
	vector<shared_ptr<class Bullet>> _bullets;

	float _angle = 0.0f;
};

