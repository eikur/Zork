#include "World.h"

namespace
{
	const std::string kCommandLook = "look";
	const std::string kCommandUse = "use";
	const std::string kCommandTake = "take";
	const std::string kCommandGo = "go";
	const std::string kCommandDrop = "drop";
	const std::string kCommandInventory = "inventory";
	const std::string kCommandRead = "read";
	const std::string kCommandOpen = "open";
	const std::string kCommandTalk = "talk";
	const std::string kCommandDuel = "duel";

	const std::string kCommandLookShort = "l";
	const std::string kCommandUseShort = "u";
	const std::string kCommandTakeShort = "t";
	const std::string kCommandGoShort = "g";
	const std::string kCommandDropShort = "d";
	const std::string kCommandInventoryShort = "i";
	const std::string kCommandReadShort = "r";
	const std::string kCommandOpenShort = "o";
	const std::string kCommandTalkShort = "k";
	const std::string kCommandDuelShort = "x";
}

World::World()
{
	//rooms
	Room* house = new Room("House", "This is a wooden house. It looks rustic and worn down, and there are signs that somebody lives here, but it looks appealing. \nThere is a ladder that goes up, and the exit is to the east");
	Room* attic = new Room("House attic", "The attic is dusty, and only a few rays of light enter through the cracks of the worn out roof. A ladder goes down");
	Room* field = new Room("Crossing field", "You are in the middle of a sunny field. \nYou see in the distance a thick forest everywhere you look, and a small wooden house nearby to the west.");
	Room* forest1 = new Room("Forest", "You are in the middle of a forest. The density of vegetation and trees here make it difficult to orientate.");
	Room* forest2 = new Room("Forest", "You are in the middle of a forest. The density of vegetation and trees here make it difficult to orientate.\nYou hear a water stream in the distance");
	Room* river = new Room("River bed", "A river flows fiercely from north to south, blocking any route that once was.\nYou can see the forest to the west and a spooky cave to the east.\nYou're happy that you can cross the river without having to swim.");
	Room* cave = new Room("Cave", "It's pitch black inside. If only you could use something to light it up...", false);

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
	Link* field_to_forest2 = new Link(field, forest2, "north", "west");
	Link* forest1_to_forest2_1 = new Link(forest1, forest2, "north", "south");
	Link* forest1_to_forest2_2 = new Link(forest1, forest2, "east", "east");
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

	// npc
	hermit = new Character("hermit", "He might be like 80 years old, and what a beard! It reminds you of Kill Bill's kung fu master", forest1,
		"Nowadays there are lots of youngsters like you coming this way for fame. Poor children, there is nothing here but nature! Don't waste your time!");
	this->entities.push_back(hermit);

	//items & notes
	trunk = new Item("trunk", "This is a sturdy trunk, but it has seen better days", attic, false, true, true);
	bag = new Item("bag", "This a waterproof bag. You can stuff things inside", trunk, true, true, false);
	torch = new Item("torch", "This is an old fashioned torch. It only works well when dry", trunk, true, false, false);	

	mailbox = new Item("mailbox", "This is a pretty standard mailbox. I swear I have seen it somewhere else...", field, false, true, true);
	letter = new Note("letter", "This letter was inside the mailbox", mailbox, true, "Welcome To Zork! Good job finding this letter!\n\
You can find the game's wiki here: https://github.com/eikur/Zork/wiki \n\
I hope you enjoy this game as much as I enjoyed doing it!\n\nJorge a.k.a. eikur\n\nPS: Check also my other projects!");
	peanuts = new Item("peanuts", "This is a bag of peanuts", house, true, false, false);

	chest = new Item("chest", "This is the mistery chest that you were looking for", cave, false, true, true);
	note = new Note("note", "This is a handmade note", chest, true, "\nTo you, fellow adventurer:\nYou are too late. Many have come to these \
lands looking for a treasure, and they gone back with naught\nThere were also a few ones that were fool enough to duel with me, and they all failed.\n\
I am the only rightful heir to the treasure that was found here, and I will only hand it to someone that beats me to a duel. Not that it can happen anytime soon.\n\n\
If you feel like today's your lucky day, come and meet me. I'll be waiting.\nYou already know who I am, right?");
	sword = new Item("sword", "This is a rusty sword, but it can come in handy for an insult duel", chest, true, false, false);

	gem = new Item("prize", "This is the gem you came to this lost zone for! You can see how bright it is, you can make tons of money with it!", hermit, true, false, false);


	this->entities.push_back(trunk);
	this->entities.push_back(bag);
	this->entities.push_back(torch);
	
	this->entities.push_back(chest);
	this->entities.push_back(note);

	//player
	player = new Player("The new Nathan Drake", "You look endearing", field);

	this->entities.push_back(player);
}

World::~World()
{
	for (std::list<Entity*>::iterator iter = entities.begin(); iter != entities.end(); iter++)
		delete *iter;
	entities.clear();
}

bool World::ParsePlayerCommands(const std::vector<std::string>& commands) const
{
	bool result = true;
	
	if (!player->IsDueling())
	{
		if (AreEqual(commands[0], kCommandLook) || AreEqual(commands[0], kCommandLookShort)) {
			player->Look(commands);
		}
		else if (AreEqual(commands[0], kCommandGo) || AreEqual(commands[0], kCommandGoShort)) {
			player->Go(commands);
		}
		else if (AreEqual(commands[0], kCommandTake) || AreEqual(commands[0], kCommandTakeShort)) {
			player->Take(commands);
		}
		else if (AreEqual(commands[0], kCommandDrop) || AreEqual(commands[0], kCommandDropShort)) {
			player->Drop(commands);
		}
		else if (AreEqual(commands[0], kCommandInventory) || AreEqual(commands[0], kCommandInventoryShort)) {
			player->Inventory();
		}
		else if (AreEqual(commands[0], kCommandOpen) || AreEqual(commands[0], kCommandOpenShort)) {
			player->Open(commands);
		}
		else if (AreEqual(commands[0], kCommandRead) || AreEqual(commands[0], kCommandReadShort)) {
			player->Read(commands);
		}
		else if (AreEqual(commands[0], kCommandUse) || AreEqual(commands[0], kCommandUseShort)) {
			player->Use(commands);
		}
		else if (AreEqual(commands[0], kCommandTalk) || AreEqual(commands[0], kCommandTalkShort)) {
			player->Talk(commands);
		}
		else if (AreEqual(commands[0], kCommandDuel) || AreEqual(commands[0], kCommandDuelShort)) {
			player->StartDuel(commands);
		}
		else
		{
			result = false;
		}
	}
	else
	{ 
		result = player->DuelAction(commands);
	}

	return result;
}

void World::GetPlayerCommands(const std::vector<std::string>& commands) const
{
	bool result = ParsePlayerCommands(commands);

	if (!result)
	{
		std::cout << "Sorry, I didn't quite get your command" << std::endl;
	}
}