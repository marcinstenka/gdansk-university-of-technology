#include <iostream>

#include "World.h"
#include "Organism.h"
#include "Plant.h"
#include "Guarana.h"

Guarana::Guarana() : Plant() {
	_strength = 0;
}

Guarana::Guarana(int x, int y, World* World) : Plant(0, x, y, World) {
}

char Guarana::getSymbol() const {
	return _symbol;
}

string Guarana::getName() const {
	return "Guarana";
}

void Guarana::action() {
	int randomNumber = rand() % 100;
	if (randomNumber < _probability) {
		Plant::action();
	}
}

void Guarana::colision(Organism* attacker) {
	if (this->getStrength() > attacker->getStrength()) {
		this->eventKilling(attacker);
		_World->deleteOrganism(attacker);
	}
	else {
		attacker->eventKilling(this);
		attacker->setStrength(attacker->getStrength() + 3);
		string event = this->getName() + ": strength " + attacker->getName() + " + 3 points";
		_World->addEvent(event);
		_World->putOrganismOnPoint(this->getX(), this->getY(), attacker);
		_World->deleteOrganism(this);
		attacker->print();
	}
}