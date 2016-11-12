#include "Item.h"

Item::Item(const char* name, const char* description, Room* parent, bool takeable) : Entity(name, description, parent), takeable(takeable)
{
	type = ITEM;
}

Item::~Item()
{
}

void Item::Look() const
{
	cout << "** " << name << " **" << endl;
	cout << description << endl;
	//list all the objects cointaining them
}

bool Item::IsTakeable() const
{
	return takeable;
}
