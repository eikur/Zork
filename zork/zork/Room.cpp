#include "Room.h"
#include "Link.h"
#include "Character.h"
#include "Item.h"


Room::Room(const char* name, const char* description) : Entity(name, description, NULL)
{
	type = ROOM;
}

Room::~Room()
{}

void Room::Look() const
{
	// Room > Characters > Items
	cout << "** " << name << " **" << endl;
	cout << description << endl;

	for (list<Entity*>::const_iterator it = children.begin(); it != children.end(); ++it)
	{
		if ((*it)->type == CHARACTER)
		{
			Character* ch = (Character*)(*it);
			cout << "There is someone here: " << ch->name << endl;
		}
	}

	for (list<Entity*>::const_iterator it = children.begin(); it != children.end(); ++it)
	{
		if ((*it)->type == ITEM)
		{
			Item* item = (Item*)(*it);
			cout << "There is an item here: " << item->name << endl;
			if (item->HasStorage() && !item->IsLocked())
			{
				if (item->children.size() > 0)
				{
					cout << " " << item->name << " contents:" << endl;
					for (list<Entity*>::const_iterator it2 = item->children.begin(); it2 != item->children.end(); ++it2)
						cout << "  *" << (*it2)->name << endl;
				}
			}
			
		}
	}
}

Link* Room::GetLinkTo(const string& direction) const
{
	for (list<Entity*>::const_iterator it = children.begin(); it != children.end(); ++it)
	{
		if( (*it)->type == LINK)
		{ 
			Link* link = (Link*)(*it);
			if (AreEqual(link->GetDirectionFrom(this), direction))
				return link;
		}
	}
	return NULL;
}
