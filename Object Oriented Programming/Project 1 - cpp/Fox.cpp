#include <iostream>

#include "World.h"
#include "Organism.h"
#include "Animal.h"
#include "Fox.h"

Fox::Fox() : Animal()
{
	_strength = 3;
	_initiative = 7;
}

Fox::Fox(int x, int y, World* World) : Animal(3, 7, x, y, World) {
}

void Fox::setMove(char move) {
	Animal::setMove(move);
}

int Fox::getLastMove() const {
	return Animal::getLastMove();
}

char Fox::getSymbol() const {
	return _symbol;
}

string Fox::getName() const {
	return "Fox";
}

void Fox::action() {
	Animal::runAway();
}

void Fox::colision(Organism* attacker) {
	Animal::colision(attacker);
}