#pragma once

#define GREEN_COLOR		0
#define RED_COLOR		1

class CircleCollider : public Collider
{
public:
	CircleCollider(Vector2 center, float radius);
	~CircleCollider();

	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	virtual bool IsCollision(Vector2 point) override;
	virtual bool IsCollision(shared_ptr<CircleCollider> other) override;
	virtual bool IsCollision(shared_ptr<RectCollider> other) override;

public:
	float _radius;
};

