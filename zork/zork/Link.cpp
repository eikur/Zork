#include "Link.h"
#include "Room.h"

Link::Link(Room* origin, Room* destination, const std::string& ori_to_dest, const std::string& dest_to_ori) :
	Entity("", "", EntityType::LINK, (Entity*)origin), destination(destination), origin_to_destination(ori_to_dest), destination_to_origin(dest_to_ori)
{
	destination->children.push_back(this);
}
Link::~Link() {}

std::string Link::GetDirectionFrom(const Room* starting_point) const
{
	if (starting_point == parent)
		return origin_to_destination;
	else
		return destination_to_origin;
}

Room* Link::GetDestinationFrom(const Room* starting_point) const 
{
	return (starting_point == parent) ? destination : static_cast<Room*>(parent);
}