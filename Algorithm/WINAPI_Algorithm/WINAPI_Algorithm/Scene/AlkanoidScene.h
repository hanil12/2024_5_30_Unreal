#pragma once

class PlayerBar;
class PlayerBall;

class AlkanoidScene : public Scene
{
public:
	AlkanoidScene();
	~AlkanoidScene();

	void BeforeFireUpdate();
	void Fire();

	void Update() override;
	void Render(HDC hdc) override;

private:
	bool _isFired = false;

	shared_ptr<PlayerBar> _playerBar;
	shared_ptr<PlayerBall> _playerBall;
};

