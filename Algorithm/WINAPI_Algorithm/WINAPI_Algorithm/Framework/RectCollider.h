#pragma once

class RectCollider : public Collider, public enable_shared_from_this<RectCollider>
{
public:
	RectCollider(Vector2 center, Vector2 halfSize);
	~RectCollider();

	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	virtual bool IsCollision(Vector2 point) override;
	virtual bool IsCollision(shared_ptr<class CircleCollider> other) override;
	virtual bool IsCollision(shared_ptr<RectCollider> other) override;

	float Left() { return _center._x - _halfSize._x; }
	float Right() { return _center._x + _halfSize._x; }
	float Top() { return _center._y - _halfSize._y; }
	float Bottom() { return _center._y + _halfSize._y; }

public:
	Vector2 _halfSize;
};

