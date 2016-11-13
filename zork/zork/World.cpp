#include "World.h"


World::World()
{
	//rooms
	Room* house = new Room("House", "This is a wooden house. It looks rustic and worn down, and there are signs that somebody lives here, but it looks appealing. \nThere is a ladder that goes up, and the door is to the east");
	Room* attic = new Room("House attic", "The attic is dusty, and only a few rays of light enter through the cracks of the worn out roof.");
	Room* field = new Room("Crossing field", "You are in the middle of a sunny field. \nYou see in the distance a thick forest everywhere you look, and a small wooden house nearby to the west.");
	Room* forest1 = new Room("Forest", "You are in the middle of a forest. The density of vegetation and trees here make it difficult to orientate.");
	Room* forest2 = new Room("Forest", "You are in the middle of a forest. The density of vegetation and trees here make it difficult to orientate.\nYou hear a water stream in the distance");
	Room* river = new Room("River bed", "A river flows from north to south, and you can see a spooky cave to the east.\nYou can cross the river but there is no way of getting to the other side without swimming.");
	Room* cave = new Room("Cave", "It's pitch black inside. If only you had something to light it up...", false);

	this->entities.push_back(house);
	this->entities.push_back(attic);
	this->entities.push_back(field);
	this->entities.push_back(forest1);
	this->entities.push_back(forest2);
	this->entities.push_back(river);
	this->entities.push_back(cave);

	// links between rooms
	Link* house_to_attic = new Link(house, attic, "up", "down");
	Link* house_to_field = new Link(house, field, "east", "west");
	Link* field_to_forest1_1 = new Link(field, forest1, "south", "south");
	Link* field_to_forest1_2 = new Link(field, forest1, "east", "west");
	Link* field_to_forest2 = new Link(field, forest2, "north", "east");
	Link* forest1_to_forest2_1 = new Link(forest1, forest2, "north", "south");
	Link* forest1_to_forest2_2 = new Link(forest1, forest2, "east", "west");
	Link* forest2_to_river = new Link(forest2, river, "north", "west");
	Link* river_to_cave = new Link(river, cave, "east", "west");

	this->entities.push_back(house_to_attic);
	this->entities.push_back(house_to_field);
	this->entities.push_back(field_to_forest1_1);
	this->entities.push_back(field_to_forest1_2);
	this->entities.push_back(field_to_forest2);
	this->entities.push_back(forest1_to_forest2_1);
	this->entities.push_back(forest1_to_forest2_2);
	this->entities.push_back(forest2_to_river);
	this->entities.push_back(river_to_cave);
	
	//items & notes
	trunk = new Item("trunk", "This is a sturdy trunk, but it has seen better days", attic, false, true, true);
	bag = new Item("bag", "This a waterproof bag. You can stuff things inside", trunk, true, true, false);
	torch = new Item("torch", "This is an old fashioned torch. It only works well when dry", field, true, false, false);	// change location later

	mailbox = new Item("mailbox", "This is a pretty standard mailbox. I swear I have seen it somewhere else...", house, false, true, true);
	letter = new Note("letter", "This letter was inside the mailbox", mailbox, true, "Welcome To Zork!\nI hope you didn't bust the mailbox \
open to get this letter, or somebody will be mad at you!\nEnjoy the game!");
	peanuts = new Item("peanuts", "This is a bag of peanuts", house, true, false, false);

	chest = new Item("chest", "This is the mistery chest that you were looking for", cave, false, true, true);
	note = new Note("note", "This is a handmade note", chest, true, "\nTo you, fellow adventurer:\nYou are too late. Many have come to these \
lands looking for a treasure, and they gone back with naught\nThere were also a few ones that were fool enough to duel with me, and they all failed.\n\
I am the only rightful heir to the treasure that was found here, and I will only hand it to someone that beats me to a duel. Not that it can happen anytime soon.\n\n\
If you feel like today's your lucky day, come and meet me. I'll be waiting.\nYou already know who I am, right?");
	sword = new Item("sword", "This is a rusty sword, but it can come in handy for an insult duel", chest, true, false, false);

	this->entities.push_back(trunk);
	this->entities.push_back(bag);
	this->entities.push_back(torch);
	
	this->entities.push_back(chest);
	this->entities.push_back(note);


	// characters
	npc1 = new Character("hermit", "He might be like 80 years old, and what a beard! It reminds you of Kill Bill's kung fu master", forest1,
		"Nowadays there are lots of youngsters like you coming this way for fame. Poor children, there is nothing here but nature! Don't waste your time!");
	player = new Player("The new Nathan Drake", "You look endearing", field);
	
	this->entities.push_back(npc1);
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
	bool result = true;
	
	if (AreEqual(commands[0],"look") || AreEqual(commands[0], "l") ) {
		player->Look(commands);
	}
	else if (AreEqual(commands[0], "go") || AreEqual(commands[0], "g")) {
		player->Go(commands);
	}
	else if (AreEqual(commands[0], "take") || AreEqual(commands[0], "t")) {
		player->Take(commands);
	}
	else if (AreEqual(commands[0], "drop") || AreEqual(commands[0], "d")) {
		player->Drop(commands);
	}
	else if (AreEqual(commands[0], "inventory") || AreEqual(commands[0], "i")) {
		player->Inventory();
	}
	else if (AreEqual(commands[0], "open") || AreEqual(commands[0], "o")) {
		player->Open(commands);
	}
	else if (AreEqual(commands[0], "read") || AreEqual(commands[0], "r")) {
		player->Read(commands);
	}
	else if (AreEqual(commands[0], "use") || AreEqual(commands[0], "u")) {
		player->Use(commands);
	}
	else if (AreEqual(commands[0], "talk") || AreEqual(commands[0], "k")) {
		player->Talk(commands);
	}
	else if (AreEqual(commands[0], "duel") || AreEqual(commands[0], "x")) {
		player->Duel(commands);
	}
	else
	{
		result = false;
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