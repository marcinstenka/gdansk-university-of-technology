#include <iostream>

#include "World.h"
#include "Organism.h"
#include "Plant.h"
#include "pineBorscht.h"
#define FIELDS_AROUND 4
pineBorscht::pineBorscht() : Plant() {
	_strength = 10;
}

pineBorscht::pineBorscht(int x, int y, World* World) : Plant(10, x, y, World) {
}

char pineBorscht::getSymbol() const {
	return _symbol;
}

string pineBorscht::getName() const {
	return "Borscht";
}

void pineBorscht::action() {
	Organism** org = new Organism * [FIELDS_AROUND];
	org[0] = _World->getBoardPoint(_x, _y - 1);
	org[1] = _World->getBoardPoint(_x + 1, _y);
	org[2] = _World->getBoardPoint(_x, _y + 1);
	org[3] = _World->getBoardPoint(_x - 1, _y);

	if ((org[0] != nullptr) && org[0]->isAnimal()) {
		this->eventKilling(org[0]);
		_World->deleteOrganism(org[0]);
	}
	if ((org[1] != nullptr) && org[1]->isAnimal()) {
		this->eventKilling(org[1]);
		_World->deleteOrganism(org[1]);
	}
	if ((org[2] != nullptr) && org[2]->isAnimal()) {
		this->eventKilling(org[2]);
		_World->deleteOrganism(org[2]);
	}
	if ((org[3] != nullptr) && org[3]->isAnimal()) {
		this->eventKilling(org[3]);
		_World->deleteOrganism(org[3]);
	}
	int randomNumber = rand() % 100;
	if (randomNumber < _probability) {
		Plant::action();
	}
}

void pineBorscht::colision(Organism* attacker) {
	attacker->eventKilling(this);
	_World->deleteOrganism(attacker);
}