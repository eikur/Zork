#include "Item.h"

Item::Item(const char* name, const char* description, Room* parent) : Entity(name, description, parent)
{
	type = ITEM;
}

Item::~Item()
{
}

void Item::Look() const
{
	cout << "Item: " << name << endl;
	cout << description << endl;
	//list all the objects cointaining them
}

