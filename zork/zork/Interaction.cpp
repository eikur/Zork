#include "Interaction.h"

Interaction::Interaction(const char* code, const char* description, InteractionType type, Interaction* response_to) :
	code(code), description(description), type(type), response_to(response_to) {
}

Interaction::~Interaction(){}

void Interaction::Print() {
	cout << code << " - " << description << endl;
}

void Interaction::Say() {
	cout << description << endl << endl;
}