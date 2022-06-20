#include <iostream>

#include "World.h"
#include "Organism.h"
#include "Animal.h"
#include "Sheep.h"

Sheep::Sheep() : Animal() {
	_strength = 4;
	_initiative = 4;
}

Sheep::Sheep(int x, int y, World* World) : Animal(4, 4, x, y, World) {

}

void Sheep::setMove(char move) {
	Animal::setMove(move);
}

int Sheep::getLastMove() const {
	return Animal::getLastMove();
}

char Sheep::getSymbol() const {
	return _symbol;
}

string Sheep::getName() const {
	return "Sheep";
}

void Sheep::action() {
	Animal::action();
}

void Sheep::colision(Organism* attacker) {
	Animal::colision(attacker);
}