#ifndef LINK_H
#define LINK_H

#include "Entity.h"
class Room;

using namespace std;

class Link : public Entity
{
public:
	Link(Room* origin, Room* destination, const char* ori_to_dest, const char* dest_to_ori);
	~Link();

	Room *destination;
	const string origin_to_destination;
	const string destination_to_origin;

	string GetDirectionFrom(const Room* starting_point) const;
};

#endif 
