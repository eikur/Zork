#include "Note.h"

Note::Note(const char* name, const char* description, Entity* parent, bool takeable, string text) :
	Item(name, description, parent, takeable, false, false), text(text) 
{
	type = NOTE;
}

Note::~Note()
{}

void Note::Read() const
{
	cout << text << endl;
}