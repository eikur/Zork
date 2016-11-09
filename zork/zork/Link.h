#ifndef LINK_H
#define LINK_H

#include "Entity.h"
#include "Room.h"

class Link : public Entity
{
public:
	Link(Room* origin, Room* destination, const char* ori_to_dest, const char* dest_to_ori);
	~Link();
public:
	Room* destination;
	const string origin_to_destination;
	const string destination_to_origin;

};
#endif 
