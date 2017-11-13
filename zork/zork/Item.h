#pragma once

#include "Entity.h"


class Item : public Entity
{
public:
	Item(const std::string& name, const std::string& description, Entity* parent, bool takeable, bool storage, bool locked);
	~Item();

	void Look() const;
	bool IsTakeable() const;
	bool IsStorage() const;
	bool IsLocked() const;
	void Unlock();

	virtual void Use() const {}
	virtual void Read() const {}

private:
	bool _takeable = false;
	bool _storage = false;
	bool _locked = false;
};
