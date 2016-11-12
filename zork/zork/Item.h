#ifndef ITEM_H
#define ITEM_H

#include "Entity.h"
#include "Room.h"

using namespace std; 

class Item : public Entity
{
public:
	Item(const char* name, const char* description, Entity* parent, bool takeable, bool storage, bool locked);
	~Item();

	void Look() const;
	bool IsTakeable() const;
	bool HasStorage() const;
	bool IsLocked() const;
	void Unlock();

private:
	bool takeable;
	bool storage;
	bool locked;
};
#endif
