#include "Player.h"
#include "Room.h"
#include "Link.h"
#include "Item.h"
#include "Entity.h"
#include "Note.h"
#include "Duel.h"

Player::Player( const char* name, const char* description, Room* parent ):Character(name, description, parent){
	type = PLAYER;
	in_a_duel = false;
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
			if (CanSee())
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
						if (item->HasStorage() && !item->IsLocked() && item->children.size() > 0)
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
			cout << "I can't find That" << endl;

		}
	}
	else
		parent->Look();
}

void Player::Go(const vector<string>& args) {
	if (args.size() == 1)
	{
		cout << "If only I could know the direction... (north/south/east/west/up/down)" << endl;
		return;
	}
	Link* link = GetRoom()->GetLinkTo(args[1]);
	if (link == NULL)
	{
		if(AreEqual(args[1],"north") || AreEqual(args[1],"south") || AreEqual(args[1],"west") || AreEqual(args[1], "east") || AreEqual(args[1], "up") || AreEqual(args[1], "down"))
		{
			cout << "There is not an exit in that direction" << endl;
			return;
		}
		cout << "That is not a direction I recognize... (north/south/east/west/up/down)" << endl;
	}
	SetNewParent(link->GetDestinationFrom((Room*)parent));
	parent->Look();

}

void Player::Take(const vector<string>& args)
{
	if (!CanSee())
	{
		cout << "It's too dark in here!" << endl;
		return;
	}
	if (args.size() == 1)
	{
		cout << "I don't know what to take" << endl;
		return;
	}
	Entity* target = GetRoom()->Find(args[1], ITEM);
	if (target == NULL)
		target = GetRoom()->Find(args[1], NOTE);
	if (target == NULL)
	{
		cout << "I can't see any item by that name" << endl;
		return;
	}

	if (target->parent->type == ITEM)
	{
		Item* container = (Item*)target->parent;
		if (container->IsLocked())
		{
			cout << "I can't see any item by that name" << endl;
			return;
		}
	}
	if (target->IsTakeable() == true)
	{
		target->SetNewParent(this);
		cout << "Taken" << endl;
	}
	else
		cout << "This is an item that I cannot take with me" << endl;
}

void Player::Drop(const vector<string>& args)
{
	if (!CanSee())
	{
		cout << "It's too dark in here!" << endl;
		return;
	}
	if (args.size() == 1)
	{
		cout << "I don't know what to drop" << endl;
		return;
	}
	Entity* drop = this->Find(args[1], ITEM);
	if (drop == NULL)
		drop = this->Find(args[1], NOTE);
	if (drop == NULL)
	{
		cout << "I can't drop something I don't own!" << endl;
		return;
	}
	if (args.size() == 2)
	{
		drop->SetNewParent(this->parent);
		cout << "Dropped" << endl;
	}
	else if (args.size() == 4)
	{
		Item* destination = (Item*) this->Find(args[3], ITEM);
		if (destination == NULL)
		{
			destination = (Item*)GetRoom()->Find(args[3], ITEM);
			if (destination == NULL)
			{
				cout << "Are you serious?" << endl;
				return;
			}
		}
		if (destination->HasStorage() && !destination->IsLocked())
		{
			drop->SetNewParent(destination);
			cout << "Dropped " << drop->name << " into " << destination->name << endl;
		}
		else
		{
			cout << "I can't drop " << drop->name << " into " << destination->name << endl;
		}
	}
	else
	{
		cout << "I understood up to the drop part" << endl;
	}
}

void Player::Inventory() const
{
	if (children.size() == 0)
	{
		cout << "I don't own anything" << endl;
		return;
	}
	cout << "I own:" << endl;
	for (list<Entity*>::const_iterator it = children.begin(); it != children.end(); ++it)
	{
		cout << " *" << (*it)->name << endl;
	}
}

void Player::Open(const vector<string>& args) {
	if (!CanSee())
	{
		cout << "It's too dark in here!" << endl;
		return;
	}
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
	if (item->IsLocked())
	{
		item->Unlock();
		cout << "Opened" << endl;
		item->Look();
	}
	else
		cout << "It's not as if it's closed..." << endl;
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
		cout << "I don't own anything by that name that can be read" << endl;
		return;
	}
	n->Read();
}

void Player::Use(const vector<string>& args) {
	if (args.size() == 1)
	{
		cout << "I don't know what I should use" << endl;
		return;
	}
	Entity* target = this->Find(args[1], ITEM);
	if (target == NULL)
	{
		target = this->Find(args[1], NOTE);
		if (target == NULL)
		{
			cout << "I can't use something I don't find in my inventory" << endl;
			return;
		}
		else
		{
			cout << "Maybe I should not try to use it, but to read it" << endl;
			return;
		}
	}
	if (AreEqual(target->name, "torch"))
	{
		cout << "Litting the torch!" << endl;
		if (AreEqual(parent->name,"Cave"))
		{
			Room* cave = (Room*)parent;
			cout << "You lit the cave!" << endl << endl;
			cave->description = "This looks like a millenial cave, not known to man, waiting here to be discovered. However, you see some dried footsteps in the mud. Did you arrive too late..?";
			cave->SetIllumination(true);			
			parent->Look();
		}
		return;
	}
	if (AreEqual(target->name, "sword"))
	{
		cout << "I am no skilled swordsman, but maybe I can win a duel with my wit..." << endl;
		return;
	}
	if (AreEqual(target->name, "peanuts"))
	{
		cout << "I am not really hungry. Maybe later!" << endl;
		return;
	}
	cout << "I understood up to the use part" << endl;
}

void Player::Talk(const vector<string>& args) const {
	if (!CanSee())
	{
		cout << "It's too dark in here!" << endl;
		return;
	}
	if (args.size() == 1)
	{
		cout << "I need somebody to talk to!" << endl;
		return;
	}
	Character* interlocutor = (Character*)GetRoom()->Find(args[1], CHARACTER);
	if (interlocutor == NULL)
	{
		cout << "I don't know who that is" << endl;
		return;
	}
	interlocutor->Talk();
}

void Player::StartDuel(const vector<string>& args) {
	if (args.size() == 1)
	{
		cout << "I'd love to duel somebody, but I need to know who!" << endl;
		return;
	}
	Character* duelist = (Character*)GetRoom()->Find(args[1], CHARACTER);
	if (duelist == NULL)
	{
		cout << "Yay! I'm gonna duel with somebody who isn't even here!" << endl;
		return;
	}
	if (this->Find("sword", ITEM) == NULL)
	{
		cout << "You can't insult duel anybody without a proper sword" << endl;
		return;
	}
	if (duelist->beaten == true)
	{
		cout << "I don't want to duel again someone I've already beaten" << endl;
		return;
	}
	duel = new Duel(this, duelist);
}

void Player::EnterDuel() {
	cout << "**  ENTERING DUEL MODE  **" << endl;
	in_a_duel = true;
}

void Player::ExitDuel() {
	in_a_duel = false;
	cout << "**  EXITING DUEL MODE  **" << endl;
}

bool Player::DuelAction(const vector<string>& args) const {
	return duel->ChooseOption(args);
}

bool Player::CanSee() const {
	return GetRoom()->IsIlluminated();
}