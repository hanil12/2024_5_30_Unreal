#pragma once
class World_3
{
public:
	World_3();
	~World_3();

	void CreateObjects();

	void Battle();

	bool End();

private:
	Creature* _boss;
	vector<Creature*> _players;
};

