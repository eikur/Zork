#include "Interaction.h"

Interaction::Interaction(const std::string& code, const std::string& description, InteractionType type, Interaction* response_to) :
	code(code), description(description), type(type), response_to(response_to) {
}

Interaction::~Interaction(){}

void Interaction::Print() {
	std::string adjust;
	if (code.length() < 5)
		adjust = "\t\t";
	else
		adjust = "\t";
	std::cout << " > " <<  code << adjust << description << std::endl;
}

void Interaction::Say() {
	std::cout << description << std::endl << std::endl;
}