#include <iostream>

#include "World.h"
#include "Organism.h"
#include "Animal.h"
#include "Wolf.h"

Wolf::Wolf() : Animal() {
	_strength = 9;
	_initiative = 5;
}

Wolf::Wolf(int x, int y, World* World) : Animal(9, 5, x, y, World) {
}

void Wolf::setMove(char move) {
	Animal::setMove(move);
}

int Wolf::getLastMove() const {
	return Animal::getLastMove();
}

char Wolf::getSymbol() const {
	return _symbol;
}

string Wolf::getName() const {
	return "Wolf";
}

void Wolf::action() {
	Animal::action();
}

void Wolf::colision(Organism* attacker) {
	Animal::colision(attacker);
}