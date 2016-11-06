#include "World.h"

World::World()
{
	//world setup
}

World::~World()
{
	for (list<Entity*>::iterator iter = entities.begin(); iter != entities.end(); iter++)
		delete *iter;
	entities.clear();
}

void World::Update()
{
	for (list<Entity*>::const_iterator iter = entities.begin(); iter != entities.end(); iter++)
		(*iter)->Update();
}