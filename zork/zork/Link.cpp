#include "Link.h"

Link::Link(Room* origin, Room* destination, const char* ori_to_dest, const char* dest_to_ori) :
	Entity("", "", (Entity*)origin), destination(destination), origin_to_destination(ori_to_dest), destination_to_origin(dest_to_ori){
	type = LINK;
	destination->children.push_back(this);
}
Link::~Link() {}

string Link::GetDirectionFrom(const Room* starting_point) const
{
	if (starting_point == parent)
		return origin_to_destination;
	if (starting_point == destination)
		return destination_to_origin;
	return origin_to_destination;
}
