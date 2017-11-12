#ifndef WORLD_H
#define WORLD_H

#include <string>
#include <list>
#include <vector>

#include "Entity.h"
#include "Room.h"
#include "Character.h"
#include "Link.h"
#include "Player.h"
#include "Item.h"
#include "Note.h"

class World 
{

public:
	World();
	~World();
	bool ParsePlayerCommands(const std::vector<std::string>& commands) const;
	void GetPlayerCommands(const std::vector<std::string>& commands) const;

private:
	std::list<Entity*> entities;
	Player* player;
	Character* hermit;
	
	Item* trunk;
	Item* bag;
	Item* torch;

	Item* mailbox;
	Note* letter;	
	Item* peanuts; 

	Item* chest;
	Note* note;	
	Item* sword;
	Item* gem;
};


#endif // WORLD_H
