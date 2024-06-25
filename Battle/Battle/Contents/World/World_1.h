#pragma once
class World_1
{
public:
	World_1();
	~World_1();

	void CreatePlayer();

	void Battle();

	bool End();

private:
	Creature* _player1;
	Creature* _player2;
};

