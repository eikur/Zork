#ifndef INTERACTION_H
#define INTERACTION_H

#include <string>
#include <iostream>

enum InteractionType {
	ATTACK,
	COMEBACK
};

class Interaction {
public:
	std::string code;
	std::string description;
	InteractionType type;
	Interaction* response_to;

	Interaction(const std::string& code, const std::string& description, InteractionType type, Interaction* response_to = nullptr);
	~Interaction();

	void Print();
	void Say();
};
#endif // !INTERACTION_H