#ifndef ITEM_H
#define ITEM_H

#include "Entity.h"
#include "Room.h"

using namespace std; 

class Item : public Entity
{
public:
	Item(const char* name, const char* description, Room* parent, bool takeable);
	~Item();

	void Look() const;
	bool IsTakeable() const;

private:
	bool takeable;
};
#endif
