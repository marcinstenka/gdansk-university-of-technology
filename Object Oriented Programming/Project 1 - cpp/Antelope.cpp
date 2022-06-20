#include <iostream>

#include "World.h"
#include "Organism.h"
#include "Animal.h"
#include "Antelope.h"

Antelope::Antelope() : Animal() {
	_strength = 4;
	_initiative = 4;
}

Antelope::Antelope(int x, int y, World* World) : Animal(4, 4, x, y, World) {
}

void Antelope::setMove(char move) {
	Animal::setMove(move);
}

int Antelope::getLastMove() const {
	return Animal::getLastMove();
}

char Antelope::getSymbol() const {
	return _symbol;
}

string Antelope::getName() const {
	return "Antelope";
}


void Antelope::action()
{
	_World->putOrganismOnPoint(_x, _y, nullptr);
	this->moveSeveralTimes(2);
}

void Antelope::colision(Organism* attacker) {
	int randomNumber = rand() % 100 + 1;
	if (randomNumber % 2 == 0 && attacker->getSymbol() != _symbol) {
		this->moveToEmptyField();
		if (_lastMove != 0) {
			return;
		}
	}
	Animal::colision(attacker);
}