#ifndef __Room__
#define __Room__

#include <iostream>
#include "Entity.h"

using namespace std;

class Room : public Entity
{
public:
	Room(const char* name, const char* description);
	~Room();

	void Look() const;
};
#endif // !__Room__

