#include "Link.h"

Link::Link(Room* origin, Room* destination, const char* ori_to_dest, const char* dest_to_ori) :
	Entity("", "", (Entity*)origin), destination(destination), origin_to_destination(ori_to_dest), destination_to_origin(dest_to_ori){
	
	destination->childs.push_back(this);
}
Link::~Link() {}