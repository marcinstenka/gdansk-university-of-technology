#include <iostream>

#include "World.h"
#include "Organism.h"
#include "Plant.h"
#include "Grass.h"

Grass::Grass() : Plant() {
	_strength = 0;
}

Grass::Grass(int x, int y, World* World) : Plant(0, x, y, World) {
}

char Grass::getSymbol() const {
	return _symbol;
}

string Grass::getName() const {
	return "Grass";
}

void Grass::action() {
	int randomNumber = rand() % 100;
	if (randomNumber < _probability) {
		Plant::action();
	}
}

void Grass::colision(Organism* attacker) {
	Plant::colision(attacker);
}