#include "World.h"


World::World()
{
	Room* house = new Room("House", "");
	Room* attic = new Room("House attic", "The attic is dusty, and only a few rays of light enter through the cracks of the worn out roof.");
	Room* field = new Room("Crossing field", "You are in the middle of a field. You see in the distance a thick forest everywhere you look, and a small wooden house nearby to the east.");
	Room* forest1 = new Room("Forest", "You are in the middle of a forest. The density of vegetation and trees here make it difficult to orientate.");
	Room* forest2 = new Room("Forest", "You are in the middle of a forest. The density of vegetation and trees here make it difficult to orientate. You hear a water stream in the distance");
	Room* river = new Room("River bed", "A river flows from north to south, and you can see a spooky cave to the east. You can cross the river but there is no way of getting to the other side without swimming.");
	Room* cave = new Room("Cave", "It's pitch black inside");

	this->entities.push_back(house);
	this->entities.push_back(attic);
	this->entities.push_back(field);
	this->entities.push_back(forest1);
	this->entities.push_back(forest2);
	this->entities.push_back(river);
	this->entities.push_back(cave);
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