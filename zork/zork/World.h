#ifndef WORLD_H
#define WORLD_H

#include <string>
#include <list>
#include <vector>

#include "Entity.h"
#include "Room.h"
#include "Character.h"
#include "Link.h"


using namespace std;

class World 
{

public:
	World();
	~World();
	void Update();
	bool ParsePlayerCommands(const vector<string>& commands) const;
	void GetPlayerCommands(const vector<string>& commands) const;

private:
	list<Entity*> entities;

};


#endif // WORLD_H
