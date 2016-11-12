#include "Player.h"
#include "Room.h"
#include "Link.h"
#include "Item.h"
#include "Entity.h"
#include "Note.h"

Player::Player( const char* name, const char* description, Room* parent ):Character(name, description, parent){
	type = PLAYER;
}

Player::~Player(){}

void Player::Look(const vector<string>& args) const {
	if (args.size() > 1)
	{
		if (AreEqual(args[1],"me") || AreEqual(args[1],"player" ) )
		{
			cout << "** " << name << " **" << endl;
			cout << description << endl;
		}
		else
		{
			for (list<Entity*>::const_iterator it = parent->children.begin(); it != parent->children.end(); ++it)
			{
				if (AreEqual((*it)->name, args[1]))
				{
					(*it)->Look();
					return;
				}
				if ((*it)->type == ITEM)
				{
					Item* item = (Item*)(*it);
					if (item->HasStorage() && !item->IsLocked() &&  item->children.size() > 0)
					{
						for (list<Entity*>::const_iterator it2 = item->children.begin(); it2 != item->children.end(); ++it2)
						{
							if (AreEqual((*it2)->name, args[1])) {
								(*it2)->Look();
								return;
							}
						}
					}
				}
			}
			for (list<Entity*>::const_iterator it = this->children.begin(); it != this->children.end(); ++it)
			{
				if (AreEqual((*it)->name, args[1]))
				{
					(*it)->Look();
					return;
				}
				Item* item = (Item*)(*it);
				if (item->HasStorage() && item->children.size() >0 )
				{
					for (list<Entity*>::const_iterator it2 = item->children.begin(); it2 != item->children.end(); ++it2)
					{
						if (AreEqual((*it2)->name, args[1])) {
							(*it2)->Look();
							return;
						}
					}
				}
			}
			cout << "I can't find what you are looking for" << endl;

		}
	}
	else
		parent->Look();
}

void Player::Go(const vector<string>& args) {
	if (args.size() == 1)
	{
		cout << "I don't know where to go" << endl;
		return;
	}
	Link* link = GetRoom()->GetLinkTo(args[1]);
	if (link == NULL)
	{
		cout << "There is nowhere to go in that direction" << endl;
		return;
	}
	SetNewParent(link->GetDestinationFrom((Room*)parent));
	parent->Look();

}

void Player::Take(const vector<string>& args)
{
	if (args.size() == 1)
	{
		cout << "I don't know what to take" << endl;
		return;
	}
	Item* item = (Item*)GetRoom()->Find(args[1], ITEM);
	if (item == NULL)
	{
		cout << "I can't see any item by that name" << endl;
		return;
	}
	
	if (item->parent->type == ITEM )
	{
		Item* container = (Item*)item->parent;
		if (container->IsLocked())
		{
			cout << "I can't see any item by that name" << endl;
			return;
		}
	}
	if(item->IsTakeable() == true)
	{
			item->SetNewParent(this);
			cout << "Taken" << endl;
	}
	else
		cout << "This is an item that I cannot take with me" << endl; 
}

void Player::Drop(const vector<string>& args)
{
	if (args.size() == 1)
	{
		cout << "I don't know what to drop" << endl;
		return;
	}
	
	Item* item = (Item*) this->Find(args[1], ITEM);
	if (item == NULL)
	{
		cout << "I can't drop something I don't own!" << endl;
		return;
	}
	if (args.size() == 2)
	{
		item->SetNewParent(this->parent);
		cout << "Dropped" << endl;
	}
	else if (args.size() == 4)
	{
		Item* destination = (Item*) this->Find(args[3], ITEM);
		if (destination == NULL)
		{
			destination = (Item*) GetRoom()->Find(args[3], ITEM);
			if (destination == NULL)
			{
				cout << "I can't find item " << args[3] << " in the inventory nor in your surroundings" << endl;
				return;
			}
		}
		if (destination->HasStorage() && !destination->IsLocked())
		{
			item->SetNewParent(destination);
			cout << "Dropped " << item->name << " into " << destination->name << endl;
		}
		else
		{
			cout << "You can't drop " << item->name << " into " << destination->name << endl;
		}
	}
	else
	{
		cout << "I understood you up to the drop part" << endl;
	}
}

void Player::Inventory(const vector<string>&) const
{
	if (children.size() == 0)
	{
		cout << "You don't own anything" << endl;
		return;
	}
	cout << "You own:" << endl;
	for (list<Entity*>::const_iterator it = children.begin(); it != children.end(); ++it)
	{
		cout << (*it)->name << endl;
	}
}

void Player::Open(const vector<string>& args) {
	if (args.size() == 1)
	{
		cout << "I don't know what to open!" << endl;
		return;
	}
	Item* item = (Item*)GetRoom()->Find(args[1], ITEM);
	if (item == NULL)
	{
		cout << "I can't see any item by that name" << endl;
		return;
	}
	item->Unlock();
	cout << "Opened" << endl;
}
void Player::Read(const vector<string>& args)
{
	if (args.size() == 1)
	{
		cout << "I don't know what to read!" << endl;
		return;
	}
	Note* n = (Note*) this->Find(args[1], NOTE);
	if (n == NULL)
	{
		cout << "You don't own anything by that name that can be read" << endl;
		return;
	}
	n->Read();
}