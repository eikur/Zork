#include "Item.h"

Item::Item(const char* name, const char* description, Entity* parent, bool takeable, bool storage, bool locked) : Entity(name, description, parent), takeable(takeable), storage(storage),  locked(locked)
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
	if (HasStorage())
	{
		if (IsLocked())
			cout << "It's locked and its contents can't be seen" << endl;
		else
		{
			if (children.size() == 0)
				cout << "It's empty" << endl;
			else
			{
				cout << "It contains:" << endl;
				for (list<Entity*>::const_iterator it = children.begin(); it != children.end(); ++it)
					cout << (*it)->name << endl;
			}
		}
	}
}

bool Item::IsTakeable() const
{
	return takeable;
}
bool Item::HasStorage() const {
	return storage;
}
bool Item::IsLocked() const {
	return locked;
}