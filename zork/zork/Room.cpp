#include "Room.h"

Room::Room(const char* name, const char* description) : Entity(name, description, NULL)
{
}

Room::~Room()
{}

void Room::Look() const
{
	cout << "** " << name << " **" << endl;
	cout << description << endl;
}
