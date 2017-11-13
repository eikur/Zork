#ifndef NOTE_H
#define NOTE_H

#include "Item.h"
#include <string>

class Note : public Item {
public:
	Note(const std::string& name, const std::string& description, Entity* parent, bool takeable, const std::string& text);
	~Note();

	void Use() const override { Read(); }
	void Read() const override;

private:
	std::string text;
};

#endif