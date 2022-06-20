#include <iostream>

#include "World.h"
#include "Organism.h"
#include "Plant.h"
#include "Blueberry.h"

Blueberry::Blueberry() : Plant() {
	_strength = 99;
}

Blueberry::Blueberry(int x, int y, World* World) : Plant(99, x, y, World) {
}

char Blueberry::getSymbol() const {
	return _symbol;
}

string Blueberry::getName() const {
	return "Blueberry";
}

void Blueberry::action() {
	int randomNumber = rand() % 100;
	if (randomNumber < _probability) {
		Plant::action();
	}
}

void Blueberry::colision(Organism* attacker) {
	attacker->eventKilling(this);
	_World->deleteOrganism(attacker);
}