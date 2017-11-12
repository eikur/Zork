#include "Note.h"

Note::Note(const std::string& name, const std::string& description, Entity* parent, bool takeable, const std::string& text) :
	Item(name, description, parent, takeable, false, false, EntityType::NOTE), text(text)
{
}

Note::~Note()
{}

void Note::Read() const
{
	std::cout << text << std::endl;
}