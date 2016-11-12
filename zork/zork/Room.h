#ifndef ROOM_H
#define ROOM_H

#include <iostream>
#include "Entity.h"
#include "Character.h"
#include "Item.h"
class Link;


using namespace std;

class Room : public Entity
{
public:
	Room(const char* name, const char* description);
	~Room();

	void Look() const;
};

#endif // ROOM_H

