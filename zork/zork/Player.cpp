#include "Player.h"
#include "Room.h"
#include "Link.h"
#include "Item.h"

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
	Entity* item =  GetRoom()->Find(args[1],ITEM);
	if (item == NULL)
	{
		cout << "Sorry, I can't take that!" << endl;
		return;
	}
	item->SetNewParent(this);
	cout << "Taken" << endl;
}

void Player::Drop(const vector<string>& args)
{
	if (args.size() == 1)
	{
		cout << "I don't know what to drop" << endl;
		return;
	}
	Entity* item = this->Find(args[1], ITEM);
	if (item == NULL)
	{
		cout << "I can't drop something I don't own!" << endl;
		return;
	}
	item->SetNewParent(this->parent);
	cout << "Dropped" << endl;
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