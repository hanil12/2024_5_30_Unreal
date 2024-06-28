#pragma once
class Line2Scene : public Scene
{
public:
	Line2Scene();
	~Line2Scene();

	void Update() override;
	void Render(HDC hdc) override;

private:
	shared_ptr<Line> _line1;
	shared_ptr<Line> _line2;

	shared_ptr<CircleCollider> _circle;
};

