#ifndef INTERACTION_H
#define INTERACTION_H

#include <string>
#include <iostream>

using namespace std;

enum InteractionType {
	ATTACK,
	COMEBACK
};

class Interaction {
public:
	string code;
	string description;
	InteractionType type;
	Interaction* response_to;

	Interaction(const char* code, const char* description, InteractionType type, Interaction* response_to = NULL);
	~Interaction();

	void Print();
};
#endif // !INTERACTION_H