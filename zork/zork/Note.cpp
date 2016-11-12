#include "Note.h"

Note::Note(const char* name, const char* description, Entity* parent, bool takeable, bool storage, bool locked, string text) :
	Item(name, description, parent, takeable, storage, locked), text(text) 
{
	type = NOTE;
}

Note::~Note()
{}

void Note::Read() const
{
	cout << text << endl;
}