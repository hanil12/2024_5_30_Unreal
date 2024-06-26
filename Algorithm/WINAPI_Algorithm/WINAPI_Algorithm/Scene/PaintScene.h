#pragma once
class PaintScene : public Scene
{
public:
	PaintScene();
	~PaintScene();

	void Update() override;
	void Render(HDC hdc) override;

private:
	shared_ptr<Rect> _rect;
	// circle
};

