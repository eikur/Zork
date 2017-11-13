#include "Room.h"
#include "Link.h"
#include "Character.h"
#include "Item.h"
#include <string>

using namespace std;

Room::Room(const std::string& name, const std::string& description, bool illuminated) : Entity(name, description, EntityType::ROOM), illuminated(illuminated)
{
}

Room::~Room()
{}

void Room::Look() const
{
	// Room > Characters > Items
	cout << "** " << name << " **" << endl;
	cout << description << endl;

	if (IsIlluminated())
	{
		for (list<Entity*>::const_iterator it = children.begin(); it != children.end(); ++it)
		{
			if ((*it)->getType() == EntityType::CHARACTER)
			{
				cout << "There is someone here: " << (*it)->name << endl;
			}
		}

		for (list<Entity*>::const_iterator it = children.begin(); it != children.end(); ++it)
		{
			if ((*it)->getType() == EntityType::ITEM)
			{
				Item* item = (Item*)(*it);
				cout << "There is an item: " << item->name << endl;
				if (item->IsStorage() && !item->IsLocked())
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
}

Link* Room::GetLinkTo(const string& direction) const
{
	for (list<Entity*>::const_iterator it = children.begin(); it != children.end(); ++it)
	{
		if( (*it)->getType() == EntityType::LINK)
		{ 
			Link* link = (Link*)(*it);
			if (AreEqual(link->GetDirectionFrom(this), direction))
				return link;
		}
	}
	return nullptr;
}

bool Room::IsIlluminated() const
{
	return illuminated;
}

void Room::SetIllumination(bool new_illumination)
{
	illuminated = new_illumination;
}
