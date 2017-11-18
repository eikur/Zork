#ifndef CHARACTER_H
#define CHARACTER_H

#include "Entity.h"
#include <string>
class Room;

class Character : public Entity {
public:
	Character(const std::string& name, const std::string& description, Room* parent, const std::string& talkLine = "", EntityType type = EntityType::CHARACTER);
	~Character();

	virtual void Talk() const;
	Room* GetRoom() const;

	bool IsDueling() const;
	void GiveDuelPrize(Entity& destination);

	bool wasBeaten() const;
	void setBeaten(bool beaten);

protected:
	bool _inDuel;
	bool _beaten;

private: 
	std::string _talkLine = "";
};


#endif // CHARACTER_H
