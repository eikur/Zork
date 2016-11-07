#ifndef __World__
#define __World__

#include <string>
#include <list>
#include <vector>

#include "Entity.h"
#include "Room.h"
#include "Character.h"


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


#endif // !__World__
