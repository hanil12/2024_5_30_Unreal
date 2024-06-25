

#include "pch.h"

int main()
{
	World_1* world = new World_1();

	while (true)
	{
		world->Battle();

		if(world->End())
			break;
	}

	delete world;

	return 0;
}