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
private:
	bool _isActive = false;
	shared_ptr<Collider> _col;
	Vector2 _direction = Vector2(1,0);
	float _speed = 7.0f;

	Vector2 _downVector = Vector2();
};

