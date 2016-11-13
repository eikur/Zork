#include "Character.h"

Character::Character(const char* name, const char* description, Room* parent) : Entity(name, description,(Entity*) parent)
{
	type = CHARACTER;
	beaten = false;
}

Character::Character(const char* name, const char* description, Room* parent, const char* talk_line) : Entity(name, description, (Entity*)parent), talk_line(talk_line)
{
	type = CHARACTER;
}

Character::~Character(){}

void Character::Talk() const {
	if (!AreEqual(talk_line, ""))
	{
		cout << name << " says: " << endl;
		cout << " " << talk_line << endl;
	}
}

bool Character::IsDueling() const {
	return in_a_duel;
}
void Character::GiveDuelPrize(Entity* destination)
{
	Entity* prize = this->Find("prize", ITEM);
	prize->name = "gem";
	prize->SetNewParent(destination);
	cout << "You obtained: " << prize->name << endl;
	prize->Look();
}
Room* Character::GetRoom() const {
	return (Room*)parent;
}

