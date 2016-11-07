#include "World.h"


World::World()
{
	//world building - still not ready
	Room* room1 = new Room("Room1", "This is the room 1 description");
	Room* room2 = new Room("Room2", "This is the room 2 description");
	Room* room3 = new Room("Room3", "This is the room 3 description");

	this->entities.push_back(room1);
	this->entities.push_back(room2);
	this->entities.push_back(room3);
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

bool World::ParsePlayerCommands(const vector<string>& commands) const
{
	const int  size = commands.size();
	return true;
}

void World::GetPlayerCommands(const vector<string>& commands) const
{
	// to be erased
	/*
	for (vector<string>::const_iterator j = commands.begin(); j < commands.end(); j++)
		cout << "'" << *j << "'" << endl;
	*/
	bool result = true; 
	result = ParsePlayerCommands(commands);

	if (result == false)
		cout << "I didn't understand your command" << endl;

}