#ifndef ROOM_H
#define ROOM_H

#include <iostream>
#include "Entity.h"
class Link;

class Room : public Entity
{
public:
	Room(const std::string& name, const std::string& description, bool illuminated = true);
	~Room();

	void Look() const;
	Link* GetLinkTo(const std::string& direction) const;

	bool IsIlluminated() const;
	void SetIllumination(bool new_illumination);

private:
	bool illuminated;
};
#endif // ROOM_H

