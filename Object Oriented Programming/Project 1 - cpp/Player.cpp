#include <iostream>
#include <string>

#include "World.h"
#include "Organism.h"
#include "Animal.h"
#include "Player.h"

#define UP_KEY 72
#define RIGHT_KEY 77
#define DOWN_KEY 80
#define LEFT_KEY 75
#define UP 1
#define RIGHT 2
#define DOWN 3
#define LEFT 4

using namespace std;

Player::Player(int x, int y, World* World) : Animal(5, 4, x, y, World) {
	_activeSkillTurnNumber = 5;
	_skillActive = false;
}

void Player::setMove(char move) {
	if (move == UP_KEY) {
		_lastMove = UP;
	}
	else if (move == RIGHT_KEY) {
		_lastMove = RIGHT;
	}
	else if (move == DOWN_KEY) {
		_lastMove = DOWN;
	}
	else if (move == LEFT_KEY) {
		_lastMove = LEFT;
	}
}

void Player::setIsPlayerSkillActive(bool skillActive) {
	_skillActive = skillActive;
}

void Player::setPlayerSkillTurn(int turns) {
	_activeSkillTurnNumber = turns;
}

int Player::getLastMove() const {
	return Animal::getLastMove();
}

bool Player::isPlayerSkillActive() const {
	return _skillActive;
}

int Player::getPlayerSkillTurn() const {
	return _activeSkillTurnNumber;
}

char Player::getSymbol() const {
	return _symbol;
}

string Player::getName() const {
	return "Player";
}

string Player::write() const {
	string result = this->getName() + " " + to_string(_strength) + " " + to_string(_initiative) + " ";
	result += to_string(_x) + " " + to_string(_y) + " " + to_string(_age);
	result += " " + to_string(_skillActive) + " " + to_string(_activeSkillTurnNumber);
	return result;
}

void Player::action() {
	string event;
	event = this->getName() + ": walked";

	_World->putOrganismOnPoint(_x, _y, nullptr);
	if ((_lastMove == 1) && (_y - 1 != 0)) {
		_y -= 1;
	}
	else if ((_lastMove == 2) && (_x + 1 != _World->getN() + 1)) {
		_x += 1;
	}
	else if ((_lastMove == 3) && (_y + 1 != _World->getM() + 1)) {
		_y += 1;
	}
	else if ((_lastMove == 4) && (_x - 1 != 0)) {
		_x -= 1;
	}
	else {
		_lastMove = 0;
		this->print();
	}
	_World->addEvent(event);
}

void Player::colision(Organism* attacker) {
	Animal::colision(attacker);
}

void Player::runAway() {
	Animal::runAway();
}

void Player::activateSkill() {
	_skillActive = true;
	_activeSkillTurnNumber = 0;
	cout << "Skill is now active" << endl;
}

void Player::endPlayerSkill() {
	_skillActive = false;
	_activeSkillTurnNumber = 0;
}