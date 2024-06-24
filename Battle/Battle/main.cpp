

#include "pch.h"

int main()
{
	srand(time(nullptr));

	Creature* player = new Knight("hanil", 100, 10);
	Creature* Hop = new HopGoblin();

	player->Attack(Hop);

	delete player;
	delete Hop;
	//World* world = new World();

	//world->Battle1();

	//delete world;

	return 0;
}