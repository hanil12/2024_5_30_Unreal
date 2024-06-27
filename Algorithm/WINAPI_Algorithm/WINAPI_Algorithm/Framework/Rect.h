#pragma once

#define GREEN_COLOR		0
#define RED_COLOR		1

using ColorNum = int;
class RectCollider
{
public:
	RectCollider(Vector2 center, Vector2 halfSize);
	~RectCollider();

	void Update();
	void Render(HDC hdc);

	bool IsCollision(Vector2 point);
	bool IsCollision(shared_ptr<class CircleCollider> other);
	bool IsCollision(shared_ptr<RectCollider> other);

	void SetGreen() { SetColor(GREEN_COLOR); }
	void SetRed() { SetColor(RED_COLOR); }

public:
	void SetColor(ColorNum num);

	vector<HPEN> _pens;
	HPEN _curPen;

	Vector2 _center;
	Vector2 _halfSize;
};

