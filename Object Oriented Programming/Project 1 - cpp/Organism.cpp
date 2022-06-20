#include <iostream>

#include "World.h"
#include "Organism.h"

using namespace std;

Organism::Organism() {
	_strength = 0;
	_initiative = 0;
	_x = 0;
	_y = 0;
	_World = nullptr;
	_age = 0;
}

Organism::Organism(int strength, int initiative, int x, int y, World* World) {
	_strength = strength;
	_initiative = initiative;
	_x = x + 1;
	_y = y + 1;
	_World = World;
	_age = 0;
}

void Organism::setStrength(int strength) {
	_strength = strength;
}

void Organism::setInitiative(int initiative) {
	_initiative = initiative;
}

void Organism::setPosition(int x, int y) {
	_x = x + 1;
	_y = y + 1;
}

void Organism::setAge(int age) {
	_age = age;
}

void Organism::setID(int ID) {
	_ID = ID;
}

void Organism::SetWorld(World* World) {
	_World = World;
}

int Organism::getStrength() const {
	return _strength;
}

int Organism::Getinitiative() const {
	return _initiative;
}

int Organism::getX() const {
	return _x;
}

int Organism::getY() const {
	return _y;
}

int Organism::getAge() const {
	return _age;
}
int Organism::getID() const {
	return _ID;
}

World* Organism::GetWorld() const {
	return _World;
}

void Organism::print() {
	_World->putOrganismOnPoint(_x, _y, this);
}