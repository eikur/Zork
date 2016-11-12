#ifndef ROOM_H
#define ROOM_H

#include <iostream>
#include "Entity.h"
#include "Character.h"
#include "Item.h"
#include "Link.h"

using namespace std;

class Room : public Entity
{
public:
	Room(const char* name, const char* description);
	~Room();

	void Look() const;

	Link* GetLinkTo(const string& direction) const;

};
#endif // ROOM_H

