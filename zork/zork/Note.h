#ifndef NOTE_H
#define NOTE_H

#include "Item.h"

class Note : public Item {
public:
	Note(const char* name, const char* description, Entity* parent, bool takeable, bool storage, bool locked, string text);
	~Note();

	void Read() const;

private:
	string text;
};

#endif