#pragma once
class Block : public RectCollider
{
public:
	Block();
	~Block();

	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	void SetPosition(Vector2 pos);

	virtual void SetRed() override;
	virtual void SetGreen() override;

private:
	vector<HBRUSH> _brushes;
	int _curBrush = 0;
};
