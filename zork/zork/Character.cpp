#include "Character.h"

Character::Character(const std::string& name, const std::string& description, Room* parent, const std::string& talkLine, EntityType type) 
	: Entity(name, description, type, (Entity*)parent), _talkLine(talkLine)
{
}

Character::~Character(){}

void Character::Talk() const {
	if (!AreEqual(_talkLine, ""))
	{
		std::cout << name << " says: " << std::endl;
		std::cout << " " << _talkLine << std::endl;
	}
}

bool Character::IsDueling() const {
	return _inDuel;
}
void Character::GiveDuelPrize(Entity* destination)
{
	Entity* prize = this->Find("prize", EntityType::ITEM);
	prize->name = "gem";
	prize->SetNewParent(destination);
	std::cout << "You obtained: " << prize->name << std::endl;
	prize->Look();
}
Room* Character::GetRoom() const {
	return (Room*)parent;
}

bool Character::wasBeaten() const
{
	return _beaten;
}

void Character::setBeaten(bool beaten)
{
	_beaten = beaten;
}

