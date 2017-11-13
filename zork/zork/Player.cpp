#include "Player.h"
#include "Room.h"
#include "Link.h"
#include "Item.h"
#include "Entity.h"
#include "Note.h"
#include "Duel.h"

Player::Player(const std::string& name, const std::string& description, Room* parent)
	: Character(name, description, parent, "", EntityType::PLAYER)
{
	_inDuel = false;
}

Player::~Player(){}

void Player::Look(const std::vector<std::string>& args) const {
	if (args.size() > 1)
	{
		if (AreEqual(args[1],"me") || AreEqual(args[1],"player" ) )
		{
			std::cout << "** " << name << " **" << std::endl;
			std::cout << description << std::endl;
		}
		else
		{
			if (CanSee())
			{
				for (std::list<Entity*>::const_iterator it = parent->children.cbegin(); it != parent->children.cend(); ++it)
				{
					if (AreEqual(args[1], (*it)->name))
					{
						(*it)->Look();
						return;
					}
					if ((*it)->getType() == EntityType::ITEM)
					{
						Item* item = (Item*)(*it);
						if (item->IsStorage() && !item->IsLocked() && item->children.size() > 0)
						{
							for (std::list<Entity*>::const_iterator it2 = item->children.cbegin(); it2 != item->children.cend(); ++it2)
							{
								if (AreEqual(args[1], (*it2)->name)) {
									(*it2)->Look();
									return;
								}
							}
						}
					}
				}
			}
			std::cout << "I can't find That" << std::endl;
		}
	}
	else
	{
		GetRoom()->Look();
	}
}

void Player::Go(const std::vector<std::string>& args) {
	if (args.size() == 1)
	{
		std::cout << "If only I could know the direction... (north/south/east/west/up/down)" << std::endl;
		return;
	}
	Link* link = GetRoom()->GetLinkTo(args[1]);
	if (link == nullptr)
	{
		if(AreEqual(args[1],"north") || AreEqual(args[1],"south") || AreEqual(args[1],"west") || AreEqual(args[1], "east") || AreEqual(args[1], "up") || AreEqual(args[1], "down"))
		{
			std::cout << "There is not an exit in that direction" << std::endl;
			return;
		}
		std::cout << "That is not a direction I recognize... (north/south/east/west/up/down)" << std::endl;
		return;
	}
	SetNewParent(link->GetDestinationFrom((Room*)parent));
	parent->Look();

}

void Player::Take(const std::vector<std::string>& args)
{
	if (!CanSee())
	{
		std::cout << "It's too dark in here!" << std::endl;
		return;
	}
	if (args.size() == 1)
	{
		std::cout << "I don't know what to take" << std::endl;
		return;
	}
	Entity* target = GetRoom()->Find(args[1], EntityType::ITEM);
	if (target == nullptr)
	{
		std::cout << "I can't see any item like that in my surroundings." << std::endl;
		return;
	}

	if (target->parent->getType() == EntityType::ITEM)
	{
		Item* container = (Item*)target->parent;
		if (container->IsLocked())
		{
			std::cout << "I can't see any item by that name" << std::endl;
			return;
		}
	}
	if (target->IsTakeable() == true)
	{
		target->SetNewParent(this);
		std::cout << "Taken" << std::endl;
	}
	else
		std::cout << "This is an item that I cannot take with me" << std::endl;
}

void Player::Drop(const std::vector<std::string>& args)
{
	if (!CanSee())
	{
		std::cout << "It's too dark in here!" << std::endl;
		return;
	}
	if (args.size() == 1)
	{
		std::cout << "I don't know what to drop" << std::endl;
		return;
	}
	Entity* drop = this->Find(args[1], EntityType::ITEM);
	if (drop == nullptr)
	{
		std::cout << "I can't drop something I don't own!" << std::endl;
		return;
	}
	if (args.size() == 2)
	{
		drop->SetNewParent(this->parent);
		std::cout << "Dropped" << std::endl;
	}
	else if (args.size() == 4)
	{
		Item* destination = (Item*) this->Find(args[3], EntityType::ITEM);
		if (destination == nullptr || destination == (Item*)drop)
		{
			destination = (Item*)GetRoom()->Find(args[3], EntityType::ITEM);
			if (destination == nullptr || destination == (Item*) drop)
			{
				std::cout << "Are you serious?" << std::endl;
				return;
			}
		}
		if (destination->IsStorage() && !destination->IsLocked())
		{
			drop->SetNewParent(destination);
			std::cout << "Dropped " << drop->name << " into " << destination->name << std::endl;
		}
		else
		{
			std::cout << "I can't drop " << drop->name << " into " << destination->name << std::endl;
		}
	}
	else
	{
		std::cout << "I understood up to the drop part" << std::endl;
	}
}

void Player::Inventory() const
{
	if (children.size() == 0)
	{
		std::cout << "I don't own anything" << std::endl;
		return;
	}
	std::cout << "I own:" << std::endl;
	for (std::list<Entity*>::const_iterator it = children.cbegin(); it != children.cend(); ++it)
	{
		std::cout << " > " << (*it)->name << std::endl;
		if ((*it)->children.size() > 0)
		{
			std::cout << " It contains: " << std::endl;
			for (std::list<Entity*>::const_iterator it2 = (*it)->children.cbegin(); it2 != (*it)->children.cend(); ++it2)
				std::cout << "  - " << (*it2)->name << std::endl;
		}
	}
}

void Player::Open(const std::vector<std::string>& args) {
	if (!CanSee())
	{
		std::cout << "It's too dark in here!" << std::endl;
		return;
	}
	if (args.size() == 1)
	{
		std::cout << "I don't know what to open!" << std::endl;
		return;
	}
	Item* item = (Item*)GetRoom()->Find(args[1], EntityType::ITEM);
	if (item == nullptr)
	{
		std::cout << "I can't see any item by that name" << std::endl;
		return;
	}
	if (item->IsLocked())
	{
		item->Unlock();
		std::cout << "Opened" << std::endl;
		item->Look();
	}
	else
		std::cout << "It's not as if it's closed..." << std::endl;
}

void Player::Read(const std::vector<std::string>& args)
{
	if (args.size() == 1)
	{
		std::cout << "I don't know what to read!" << std::endl;
		return;
	}
	Note* n = (Note*) this->Find(args[1], EntityType::ITEM);
	if (n == nullptr)
	{
		std::cout << "I don't own anything by that name that can be read" << std::endl;
		return;
	}
	n->Read();
}

void Player::Use(const std::vector<std::string>& args) {
	if (args.size() == 1)
	{
		std::cout << "I don't know what I should use" << std::endl;
		return;
	}

	Item* target = static_cast<Item*>(this->Find(args[1], EntityType::ITEM));
	
	if (target == nullptr)
	{
		std::cout << "I can't use something I don't find in my inventory" << std::endl;
		return;
	}

	if (AreEqual(target->name, "torch"))
	{
		std::cout << "Litting the torch!" << std::endl;
		if (AreEqual(parent->name,"Cave"))
		{
			Room* cave = (Room*)parent;
			if (!cave->IsIlluminated())
			{
				std::cout << "You lit the cave!" << std::endl << std::endl;
				cave->description = "This looks like a thousand year old cave, not known to man, waiting here to be discovered.\nHowever, you see some evidences that people have been here: footsteps in the mud, some abandoned flares...\nDid you arrive too late..?";
				cave->SetIllumination(true);
				parent->Look();
			}
		}
		return;
	}
	if (AreEqual(target->name, "sword"))
	{
		std::cout << "I am no skilled swordsman, but maybe I can win a duel with my wit..." << std::endl;
		return;
	}
	if (AreEqual(target->name, "peanuts"))
	{
		std::cout << "I am not an elephant, and I am not really hungry... Maybe later!" << std::endl;
		return;
	}
	if (target != nullptr)
	{
		target->Use();
		std::cout << "I don't know how society expects me to use it!" << std::endl;
	}
	else
	{
		std::cout << "I understood up to the use part" << std::endl;
	}
}

void Player::Talk(const std::vector<std::string>& args) const {
	if (!CanSee())
	{
		std::cout << "It's too dark in here!" << std::endl;
		return;
	}
	if (args.size() == 1)
	{
		std::cout << "I need somebody to talk to!" << std::endl;
		return;
	}
	Character* interlocutor = (Character*)GetRoom()->Find(args[1], EntityType::CHARACTER);
	if (interlocutor == nullptr)
	{
		std::cout << "I don't know who that is" << std::endl;
		return;
	}
	interlocutor->Talk();
}

void Player::StartDuel(const std::vector<std::string>& args) {
	if (args.size() == 1)
	{
		std::cout << "I'd love to duel somebody, but I need to know who!" << std::endl;
		return;
	}
	Character* duelist = (Character*)GetRoom()->Find(args[1], EntityType::CHARACTER);
	if (duelist == nullptr)
	{
		std::cout << "Yay! I'm gonna duel with somebody who isn't even here!" << std::endl;
		return;
	}
	if (this->Find("sword", EntityType::ITEM) == nullptr)
	{
		std::cout << "You can't insult duel anybody without a proper sword" << std::endl;
		return;
	}
	if (duelist->wasBeaten() == true)
	{
		std::cout << "I don't want to duel again someone I've already beaten" << std::endl;
		return;
	}
	duel = new Duel(this, duelist);
}

void Player::EnterDuel() {
	std::cout << "**  ENTERING DUEL MODE  **" << std::endl;
	_inDuel = true;
}

void Player::ExitDuel() {
	_inDuel = false;
	std::cout << "**  EXITING DUEL MODE  **" << std::endl;
	delete duel;
}

bool Player::DuelAction(const std::vector<std::string>& args) const {
	return duel->ChooseOption(args);
}

bool Player::CanSee() const {
	return GetRoom()->IsIlluminated();
}