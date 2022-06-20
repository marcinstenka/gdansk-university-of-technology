#include <iostream>

#include "World.h"
#include "Organism.h"
#include "Animal.h"
#include "Turtle.h"

#define UP 1
#define RIGHT 2
#define DOWN 3
#define LEFT 4

Turtle::Turtle() : Animal() {
	_strength = 2;
	_initiative = 1;
}

Turtle::Turtle(int x, int y, World* World) : Animal(2, 1, x, y, World) {
}

void Turtle::setMove(char move) {
	Animal::setMove(move);
}

int Turtle::getLastMove() const {
	return Animal::getLastMove();
}

char Turtle::getSymbol() const {
	return _symbol;
}

string Turtle::getName() const {
	return "Turtle";
}

void Turtle::action() {
	int randomNumber = rand() % 100 + 1;
	if (randomNumber % 4 == 0) {
		Animal::action();
	}
	else {
		_lastMove = 0;
	}
}

void Turtle::colision(Organism* attacker) {
	if (attacker->getStrength() < 5 && attacker->getSymbol() != _symbol) {
		attacker->goBack();
	}
	else {
		Animal::colision(attacker);
	}
}