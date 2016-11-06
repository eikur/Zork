#ifndef __World__
#define __World__

#include <list>

#include "Entity.h"

using namespace std;

class World {

public:
	World();
	~World();
	void Update();

private:
	list<Entity*> entities;

};


#endif // !__World__
