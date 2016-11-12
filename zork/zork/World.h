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

using namespace std;

class World 
{

public:
	World();
	~World();
	bool ParsePlayerCommands(const vector<string>& commands) const;
	void GetPlayerCommands(const vector<string>& commands) const;

private:
	list<Entity*> entities;
	Player* player;
	Character* npc1;
	Item* apple;
	Item* totem;
	Item* chest; 
	Item* treasure;

};


#endif // WORLD_H
