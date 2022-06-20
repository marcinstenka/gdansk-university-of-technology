#include <iostream>
#include <cstdlib>
#include <string>

#include "World.h"
#include "Organism.h"
#include "Animal.h"

#include "Wolf.h"
#include "Sheep.h"
#include "Fox.h"
#include "Turtle.h"
#include "Antelope.h"

#define UP 1
#define RIGHT 2
#define DOWN 3
#define LEFT 4
#define SIZE 20

using namespace std;

Animal::Animal() : Organism() {
	_lastMove = NULL;
}

Animal::Animal(int strength, int initiative, int x, int y, World* World) : Organism(strength, initiative, x, y, World) {
	_lastMove = NULL;
}

bool Animal::isAnimal() {
	return true;
}

int Animal::getLastMove() const {
	return _lastMove;
}
void Animal::setMove(char move) {
	_lastMove = move;
}

void Animal::action() {
	this->moveSeveralTimes(1);
}

void Animal::colision(Organism* attacker) {
	string event;
	attacker->eventKilling(this);
	if (this->getSymbol() == attacker->getSymbol() && attacker->getAge() > 0) {
		this->breed(attacker, _World);
	}
	else if (this->getSymbol() == attacker->getSymbol() && attacker->getAge() <= 0) {
		attacker->goBack();
		event = "trying to breed";
		_World->addEvent(event);
	}
	else if (this->getStrength() > attacker->getStrength()) {
		_World->deleteOrganism(attacker);
	}
	else {
		_World->putOrganismOnPoint(this->getX(), this->getY(), attacker);
		_World->deleteOrganism(this);
		attacker->print();
	}
}
Organism* Animal::createOrganism(int x, int y, World* World) {
	if (typeid(*this) == typeid(Wolf)) {
		Wolf* newAnimal = new Wolf(x - 1, y - 1, World);
		return newAnimal;
	}
	else if (typeid(*this) == typeid(Sheep)) {
		Sheep* newAnimal = new Sheep(x - 1, y - 1, World);
		return newAnimal;
	}
	else if (typeid(*this) == typeid(Fox)) {
		Fox* newAnimal = new Fox(x - 1, y - 1, World);
		return newAnimal;
	}
	else if (typeid(*this) == typeid(Turtle)) {
		Turtle* newAnimal = new Turtle(x - 1, y - 1, World);
		return newAnimal;
	}
	else if (typeid(*this) == typeid(Antelope)) {
		Antelope* newAnimal = new Antelope(x - 1, y - 1, World);
		return newAnimal;
	}
}

void Animal::breed(Organism* attacker, World* World)
{
	int* positionX = new int[6];
	int* positionY = new int[6];
	int* move = new int[6];
	int point = 0;

	int x = 0;
	int y = 0;
	int pointsNumber = 0;
	attacker->goBack();
	if (attacker->getLastMove() == UP || attacker->getLastMove() == DOWN) {
		World->generateEmptySpaces(attacker->getX(), attacker->getY(), positionX, positionY, move, &pointsNumber);
		World->generateEmptySpaces(this->getX(), this->getY(), positionX, positionY, move, &pointsNumber);

		if (pointsNumber != 0) {
			point = rand() % pointsNumber;
			Organism* org = this->createOrganism(positionX[point], positionY[point], World);
			World->addOrganism(org);
		}
	}
	else if (attacker->getLastMove() == LEFT || attacker->getLastMove() == RIGHT) {
		World->generateEmptySpaces(attacker->getX(), attacker->getY(), positionX, positionY, move, &pointsNumber);
		World->generateEmptySpaces(this->getX(), this->getY(), positionX, positionY, move, &pointsNumber);

		if (pointsNumber != 0) {
			point = rand() % pointsNumber;
			Organism* org = this->createOrganism(positionX[point], positionY[point], World);
			World->addOrganism(org);
		}
	}
}

void Animal::runAway() {
	string event;
	int* pointsX = new int[4];
	int* pointsY = new int[4];
	int* move = new int[4];
	int pointsNumber = 0;
	Organism** org = new Organism * [4]; // organisms array to check if they are around 
	Organism* beingAttacked = _World->getBoardPoint(_x, _y);
	if (beingAttacked == this) {
		_World->putOrganismOnPoint(_x, _y, nullptr);
	}
	org[0] = _World->getBoardPoint(_x, _y - 1);
	org[1] = _World->getBoardPoint(_x + 1, _y);
	org[2] = _World->getBoardPoint(_x, _y + 1);
	org[3] = _World->getBoardPoint(_x - 1, _y);

	if (_y - 1 != 0 && (org[0] == nullptr || org[0]->getStrength() <= _strength)) {
		pointsX[pointsNumber] = _x;
		pointsY[pointsNumber] = _y - 1;
		move[pointsNumber] = 1;
		pointsNumber++;
	}
	if (_x + 1 != _World->getN() + 1 && (org[1] == nullptr || org[1]->getStrength() <= _strength)) {
		pointsX[pointsNumber] = _x + 1;
		pointsY[pointsNumber] = _y;
		move[pointsNumber] = 2;
		pointsNumber++;
	}
	if (_y + 1 != _World->getM() + 1 && (org[2] == nullptr || org[2]->getStrength() <= _strength)) {
		pointsX[pointsNumber] = _x;
		pointsY[pointsNumber] = _y + 1;
		move[pointsNumber] = 3;
		pointsNumber++;
	}
	if (_x - 1 != 0 && (org[3] == nullptr || org[3]->getStrength() <= _strength)) {
		pointsX[pointsNumber] = _x - 1;
		pointsY[pointsNumber] = _y;
		move[pointsNumber] = 4;
		pointsNumber++;
	}

	event = this->getName() + " (organism ID:" + to_string(this->getID()) + "): moved";

	if (pointsNumber != 0) {
		int randomNumber = rand() % pointsNumber;
		_x = pointsX[randomNumber];
		_y = pointsY[randomNumber];
		_lastMove = move[randomNumber];
	}
	else {
		this->print();
		_lastMove = 0;
	}
	_World->addEvent(event);
}


void Animal::goBack() {
	int attackerX = this->getX();
	int attackerY = this->getY();
	if (this->getLastMove() == UP) {
		this->setPosition(attackerX - 1, attackerY);
	}
	else if (this->getLastMove() == RIGHT) {
		this->setPosition(attackerX - 2, attackerY - 1);
	}
	else if (this->getLastMove() == DOWN) {
		this->setPosition(attackerX - 1, attackerY - 2);
	}
	else if (this->getLastMove() == LEFT) {
		this->setPosition(attackerX, attackerY - 1);
	}
	this->print();
}


void Animal::eventKilling(Organism* beingAttacked) {
	string event = this->getName() + " (organism ID:" + to_string(this->getID()) + "): attacked " + beingAttacked->getName();
	_World->addEvent(event);
}

void Animal::moveToEmptyField() {
	_World->putOrganismOnPoint(_x, _y, nullptr);
	int* pointsX = new int[4];
	int* pointsY = new int[4];
	int* move = new int[4];
	int pointsNumber = 0;

	_World->generateEmptySpaces(_x, _y, pointsX, pointsY, move, &pointsNumber);

	string event = this->getName() + " (organism ID:" + to_string(this->getID()) + "): moved";

	if (pointsNumber != 0) {
		int randomNumber = rand() % pointsNumber;
		_x = pointsX[randomNumber];
		_y = pointsY[randomNumber];
		_lastMove = move[randomNumber];
	}
	else {
		this->print();
		_lastMove = 0;
	}
	_World->addEvent(event);
}

void Animal::moveSeveralTimes(int length) {
	_World->putOrganismOnPoint(_x, _y, nullptr);
	int* pointsX = new int[4];
	int* pointsY = new int[4];
	int* move = new int[4];
	int pointsNumber = 0;
	if (_y - length > 0) {
		pointsX[pointsNumber] = _x;
		pointsY[pointsNumber] = _y - length;
		move[pointsNumber] = UP;
		pointsNumber++;
	}
	if (_x + length < _World->getN() + 1) {
		pointsX[pointsNumber] = _x + length;
		pointsY[pointsNumber] = _y;
		move[pointsNumber] = RIGHT;
		pointsNumber++;
	}
	if (_y + length < _World->getM() + 1) {
		pointsX[pointsNumber] = _x;
		pointsY[pointsNumber] = _y + length;
		move[pointsNumber] = DOWN;
		pointsNumber++;
	}
	if (_x - length > 0) {
		pointsX[pointsNumber] = _x - length;
		pointsY[pointsNumber] = _y;
		move[pointsNumber] = LEFT;
		pointsNumber++;
	}

	string event = this->getName() + " (organism ID:" + to_string(this->getID()) + ") moved";

	if (pointsNumber != 0) {
		int randomNumber = rand() % pointsNumber;
		_x = pointsX[randomNumber];
		_y = pointsY[randomNumber];
		_lastMove = move[randomNumber];
	}
	else {
		this->print();
		_lastMove = 0;
	}
	_World->addEvent(event);
}


string Animal::write() const {
	string result = this->getName() + " " + to_string(_strength) + " " + to_string(_initiative) + " ";
	result += to_string(_x) + " " + to_string(_y) + " " + to_string(_age);
	return result;
}