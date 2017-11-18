#ifndef LINK_H
#define LINK_H

#include "Entity.h"
#include <string>
class Room;


class Link : public Entity
{
public:
	Link(Room* origin, Room* destination, const std::string& ori_to_dest, const std::string& dest_to_ori);
	~Link();

	Room *destination = nullptr;
	const std::string origin_to_destination;
	const std::string destination_to_origin;

	std::string GetDirectionFrom(const Room* starting_point) const;
	Room* GetDestinationFrom(const Room* starting_point) const;
};

#endif 
