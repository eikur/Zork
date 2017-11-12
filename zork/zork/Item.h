#ifndef ITEM_H
#define ITEM_H

#include "Entity.h"
#include "Room.h"

class Item : public Entity
{
public:
	Item(const std::string& name, const std::string& description, Entity* parent, bool takeable, bool storage, bool locked, EntityType type = EntityType::ITEM);
	~Item();

	void Look() const;
	bool IsTakeable() const;
	bool HasStorage() const;
	bool IsLocked() const;
	void Unlock();

private:
	bool takeable;
	bool storage;
	bool locked;
};
#endif
