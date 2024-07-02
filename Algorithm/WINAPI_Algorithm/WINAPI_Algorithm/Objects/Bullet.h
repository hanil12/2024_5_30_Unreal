#pragma once
class Bullet
{
public:
	Bullet();
	~Bullet();

	void Update();
	void Render(HDC hdc);

	void Fire(Vector2 startPos, Vector2 direction);

	void SetActive(bool isActive);
	bool IsActive() { return _isActive; }
	bool IsOut();
	void OutControll();

	// Attack1
	void Attack_Cannon(shared_ptr<class Cannon> cannon);

	// Attack2
	void Attack_Cannon();
	void SetTarget(shared_ptr<Cannon> cannon) { _target = cannon; }

private:
	bool _isActive = false;
	shared_ptr<Collider> _col;
	Vector2 _direction = Vector2(1,0);
	float _speed = 7.0f;

	Vector2 _downVector = Vector2();

	float _lifeTime = 0.0f;
	float _delayTime = 3.0f;

	// Attack2
	weak_ptr<Cannon> _target;
};

