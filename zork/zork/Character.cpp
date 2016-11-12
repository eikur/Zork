#include "Character.h"

Character::Character(const char* name, const char* description, Room* parent) : Entity(name, description,(Entity*) parent)
{
	type = CHARACTER;
}

Character::~Character()
{}

void Character::Look(const vector<string>& args) const {
}
void Character::Go(const vector<string>& args) const {}
void Character::Take(const vector<string>& args) const {}
void Character::Inventory(const vector<string>& args) const {}
void Character::Attack(const vector<string>& args) const {}
void Character::Use(const vector<string>& args) const {}
void Character::Drop(const vector<string>& args) const {}
void Character::Status(const vector<string>& args) const {}

Room* Character::GetRoom()  {
	return (Room*)parent;
}


