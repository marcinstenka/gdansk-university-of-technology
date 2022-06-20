#include <iostream>

#include "World.h"
#include "Organism.h"
#include "Plant.h"
#include "Dandelion.h"
#define DANDELION_REPRODUCTION 3

Dandelion::Dandelion() : Plant() {
	_strength = 0;
}

Dandelion::Dandelion(int x, int y, World* World) : Plant(0, x, y, World) {
}

char Dandelion::getSymbol() const {
	return _symbol;
}

string Dandelion::getName() const {
	return "Dandelion";
}

void Dandelion::action() {
	int randomNumber;
	for (int i = 0; i < DANDELION_REPRODUCTION; i++) {
		randomNumber = rand() % 100;
		if (randomNumber < _probability) {
			Plant::action();
		}
	}
}

void Dandelion::colision(Organism* attacker) {
	Plant::colision(attacker);
}