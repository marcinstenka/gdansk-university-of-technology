#include <iostream>
#include <string>

#include "World.h"
#include "Organism.h"
#include "Plant.h"

#include "Grass.h"
#include "Dandelion.h"
#include "Guarana.h"
#include "Blueberry.h"
#include "pineBorscht.h"

using namespace std;

Plant::Plant() : Organism() {
}

Plant::Plant(int strength, int x, int y, World* World) : Organism(strength, 0, x, y, World) {
}

int Plant::getLastMove() const {
	return 0;
}

string Plant::write() const {
	string result = this->getName() + " " + to_string(this->getStrength()) + " " + to_string(this->Getinitiative()) + " ";
	result += to_string(this->getX()) + " " + to_string(this->getY()) + " " + to_string(this->getAge());
	return result;
}

void Plant::action() {
	string event;
	int* pointsX = new int[4];
	int* pointsY = new int[4];
	int* move = new int[4];
	int pointsNumber = 0;
	_World->generateEmptySpaces(_x, _y, pointsX, pointsY, move, &pointsNumber);

	if (pointsNumber != 0) {
		int randomNumber = rand() % pointsNumber;
		Organism* org = this->createOrganism(pointsX[randomNumber], pointsY[randomNumber], _World);
		_World->addOrganism(org);
		event = this->getName() + " (organism ID:" + to_string(this->getID()) + "): has spread";
		_World->addEvent(event);
	}
}

void Plant::colision(Organism* attacker) {
	attacker->eventKilling(this);
	if (this->getStrength() > attacker->getStrength()) {
		_World->deleteOrganism(attacker);
	}
	else {
		_World->putOrganismOnPoint(this->getX(), this->getY(), attacker);
		_World->deleteOrganism(this);
		attacker->print();
	}
}

bool Plant::isAnimal() {
	return false;
}


void Plant::eventKilling(Organism* beingAttacked) {
	string event = this->getName() + " (organism ID:" + to_string(this->getID()) + "): attacked " + beingAttacked->getName();
	_World->addEvent(event);
}

Organism* Plant::createOrganism(int x, int y, World* World) {
	if (typeid(*this) == typeid(Grass)) {
		Grass* newPlant = new Grass(x - 1, y - 1, World);
		return newPlant;
	}
	else if (typeid(*this) == typeid(Dandelion)) {
		Dandelion* newPlant = new Dandelion(x - 1, y - 1, World);
		return newPlant;
	}
	else if (typeid(*this) == typeid(Guarana)) {
		Guarana* newPlant = new Guarana(x - 1, y - 1, World);
		return newPlant;
	}
	else if (typeid(*this) == typeid(Blueberry)) {
		Blueberry* newPlant = new Blueberry(x - 1, y - 1, World);
		return newPlant;
	}
	else if (typeid(*this) == typeid(pineBorscht)) {
		pineBorscht* newPlant = new pineBorscht(x - 1, y - 1, World);
		return newPlant;
	}
}

void Plant::setMove(char move) {}

void Plant::goBack() {}

void Plant::runAway() {}