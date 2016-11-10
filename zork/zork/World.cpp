#include "World.h"


World::World()
{
	Room* house = new Room("House", "You are inside a wooden house. It looks rustic and worn down, but it is somehow appealing. There are signs that somebody lives here");
	Room* attic = new Room("House attic", "The attic is dusty, and only a few rays of light enter through the cracks of the worn out roof.");
	Room* field = new Room("Crossing field", "You are in the middle of a sunny field. You see in the distance a thick forest everywhere you look, and a small wooden house nearby to the west.");
	Room* forest1 = new Room("Forest", "You are in the middle of a forest. The density of vegetation and trees here make it difficult to orientate.");
	Room* forest2 = new Room("Forest", "You are in the middle of a forest. The density of vegetation and trees here make it difficult to orientate. You hear a water stream in the distance");
	Room* river = new Room("River bed", "A river flows from north to south, and you can see a spooky cave to the east. You can cross the river but there is no way of getting to the other side without swimming.");
	Room* cave = new Room("Cave", "It's pitch black inside");

	Link* house_to_attic = new Link(house, attic, "up", "down");
	Link* house_to_field = new Link(house, field, "east", "west");
	Link* field_to_forest1_1 = new Link(field, forest1, "south", "south");
	Link* field_to_forest1_2 = new Link(field, forest1, "east", "west");
	Link* field_to_forest2 = new Link(field, forest2, "north", "east");
	Link* forest1_to_forest2_1 = new Link(forest1, forest2, "north", "south");
	Link* forest1_to_forest2_2 = new Link(forest1, forest2, "east", "west");
	Link* forest2_to_river = new Link(forest2, river, "east", "west");
	Link* river_to_cave = new Link(river, cave, "east", "west");

	player = new Player("The new Indiana", "Before you stands the best adventurer ever", field);

	//more stuff here :)

	this->entities.push_back(house);
	this->entities.push_back(attic);
	this->entities.push_back(field);
	this->entities.push_back(forest1);
	this->entities.push_back(forest2);
	this->entities.push_back(river);
	this->entities.push_back(cave);

	this->entities.push_back(house_to_attic);
	this->entities.push_back(house_to_field);
	this->entities.push_back(field_to_forest1_1);
	this->entities.push_back(field_to_forest1_2);
	this->entities.push_back(field_to_forest2);
	this->entities.push_back(forest1_to_forest2_1);
	this->entities.push_back(forest1_to_forest2_2);
	this->entities.push_back(forest2_to_river);
	this->entities.push_back(river_to_cave);

	this->entities.push_back(player);
}

World::~World()
{
	for (list<Entity*>::iterator iter = entities.begin(); iter != entities.end(); iter++)
		delete *iter;
	entities.clear();
}

bool World::ParsePlayerCommands(const vector<string>& commands) const
{
	const int size = commands.size();
	bool result = true;
	switch (size)
	{
		case 1:
			if (commands[0].compare("look") == 0 || commands[0].compare("l") == 0) {
				player->Look(commands);
			}
			else if (commands[0].compare("inventory") == 0 || commands[0].compare("i") == 0) {
				cout << "inventory command" << endl;
			}
			else if (commands[0].compare("status") == 0 || commands[0].compare("s") == 0){
				cout << "status command" << endl;
			}
			else {
				result = false;
			}
		break;
		case 2:
			if (commands[0].compare("look") == 0 || commands[0].compare("l") == 0) {
				player->Look(commands);
			}
			else if (commands[0].compare("go") == 0 || commands[0].compare("g") == 0) {
				player->Go(commands);
			}
			else if (commands[0].compare("take") == 0 || commands[0].compare("t") == 0) {
				cout << "take " << commands[1] << " command" << endl;
			}
			else if (commands[0].compare("drop") == 0 || commands[0].compare("d") == 0) {
				cout << "drop " << commands[1] << " command" << endl;
			}
			else if (commands[0].compare("use") == 0 || commands[0].compare("u") == 0) {
				cout << "use " << commands[1] << " command" << endl;
			}
			else if (commands[0].compare("attack") == 0 || commands[0].compare("a") == 0) {
				cout << "attack " << commands[1] << " command" << endl;
			}
			else {
				result = false;
			}
		break;
	case 4:
			if (commands[0].compare("attack") == 0 || commands[0].compare("a") == 0) {
				cout << "attack " << commands[1] << " " << commands[2] << " " << commands[3] << " command" << endl;
			}
			else if (commands[0].compare("use") == 0 || commands[0].compare("u") == 0) {
				cout << "use " << commands[1] << " " << commands[2] << " " << commands[3] << " command" << endl;
			}
			else {
				result = false;
			}
		break;
	default: result = false;
		break;
	}
	return result;
}

void World::GetPlayerCommands(const vector<string>& commands) const
{
	bool result = true; 
	result = ParsePlayerCommands(commands);

	if (result == false)
		cout << "Sorry, I didn't quite get your command" << endl;
}