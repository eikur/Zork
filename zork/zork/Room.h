#ifndef ROOM_H
#define ROOM_H

#include <iostream>
#include "Entity.h"
class Link;

using namespace std;

class Room : public Entity
{
public:
	Room(const char* name, const char* description);
	Room(const char* name, const char* description, bool illuminated);
	~Room();

	void Look() const;
	Link* GetLinkTo(const string& direction) const;

	bool IsIlluminated() const;
	void SetIllumination(bool new_illumination);

private:
	bool illuminated;
};
#endif // ROOM_H

