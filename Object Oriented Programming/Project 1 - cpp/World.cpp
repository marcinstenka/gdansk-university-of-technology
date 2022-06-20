#include <conio.h>
#include <string>

#include "Organism.h"
#include "Player.h"
#include "World.h"

#include "Wolf.h"
#include "Sheep.h"
#include "Fox.h"
#include "Turtle.h"
#include "Antelope.h"

#include "Grass.h"
#include "Dandelion.h"
#include "Guarana.h"
#include "Blueberry.h"
#include "pineBorscht.h"

#define CHAR_KEYS 224
#define UP 1
#define RIGHT 2
#define DOWN 3
#define LEFT 4
#define UP_KEY 72
#define RIGHT_KEY 77
#define DOWN_KEY 80
#define LEFT_KEY 75
#define MAX_EVENTS_PER_ORGANISM 5

using namespace std;

World::World() : World(20, 20) {
}

World::World(int n, int m) {
	_n = n;
	_m = m;

	_organismsNumberBeforeNextTurn = 0;
	_organismsNumber = 0;
	_turn = 0;
	_isPlayerAlive = false;
	_player = nullptr;
	_events = new string[MAX_EVENTS_PER_ORGANISM * n * m];
	_eventsNumber = 0;
	_lastIdOrganismNumber = 0;
	_organisms = new Organism * [n * m];

	_board = new Organism * *[m + 2];
	for (int y = 0; y < (m + 2); y++)
	{
		_board[y] = new Organism * [n + 2];
	}

	for (int y = 0; y < (m + 2); y++)
	{
		for (int x = 0; x < (n + 2); x++)
		{
			_board[y][x] = nullptr;
		}
	}
}


int World::getN() const {
	return _n;
}

int World::getM() const {
	return _m;
}

int World::getOrganismsNumber() const {
	return _organismsNumber;
}

int World::getTurn() const {
	return _turn;
}
int World::getLastIdOrganismNumber() const {
	return _lastIdOrganismNumber;
}
Organism* World::getOrganism(int i) const {
	return _organisms[i];
}

Player* World::getPlayer() const {
	return _player;
}


void World::setBoardSize(int n, int m) {
	_n = n;
	_m = m;
}

void World::putOrganismOnPoint(int x, int y, Organism* org) {
	_board[y][x] = org;
}

void World::setTurn(int turn) {
	_turn = turn;
}

void World::addEvent(string event) {
	_events[_eventsNumber] = event;
	_eventsNumber++;
}

void World::printWorld() {
	for (int i = 0; i < _eventsNumber; i++) {
		cout << _events[i] << endl;
	}
	_eventsNumber = 0;
	for (int y = 0; y < (_m + 2); y++) {
		for (int x = 0; x < (_n + 2); x++) {
			if (getBoardPoint(x, y) == nullptr) {
				if ((x == 0) || (y == 0) || (x == _n + 1) || (y == _m + 1))
					cout << '*';
				else {
					cout << ' ';
				}
			}
			else {
				cout << getBoardPoint(x, y)->getSymbol();
			}
		}
		cout << endl;
	}
	cout << "Turn: " << _turn << endl;
	cout << endl << "n - new game" << endl;
	cout << "s - save" << endl;
	cout << "Press SPACE to start your turn" << endl;
	if (!_isPlayerAlive) {
		cout << "You died" << endl;
	}
}

void World::takeTurn() {
	_organismsNumberBeforeNextTurn = _organismsNumber;
	if (_isPlayerAlive) {
		cout << endl;
		cout << "Your move! (use arrows to move)" << endl;
		if (!_player->isPlayerSkillActive() && _player->getPlayerSkillTurn() >= 5) {
			cout << "use X key - player's skill (immortality)" << endl;
		}
		else if (!_player->isPlayerSkillActive() && _player->getPlayerSkillTurn() == 0) {
			cout << "Skill is no longer active " << endl;
		}
	}
	bool didMove = true;
	if (_isPlayerAlive) {
		unsigned char key = _getch();
		unsigned char key2 = '0';
		switch (key) {
		case 'x':
			if (!_player->isPlayerSkillActive()) {
				_player->activateSkill();
				key2 = _getch();
			}
			if ((key2 != CHAR_KEYS) || (key2 == '0' && _player->isPlayerSkillActive())) {
				cout << "" << endl;
				didMove = false;
			}
			break;
		case CHAR_KEYS:
			key = _getch();
			_player->setMove(key);
			break;
		default:
			cout << "" << endl;
			didMove = false;
			break;
		}
	}
	if (didMove) {
		doActions();
	}
}

void World::doActions() {
	Organism* org;
	Organism* beingAttacked;
	Organism* attacker;
	for (int i = 0; i < _organismsNumberBeforeNextTurn; i++) {
		org = _organisms[i];
		org->action();
		beingAttacked = _board[org->getY()][org->getX()];
		if (beingAttacked == nullptr || org->getLastMove() == 0) {
			org->print();
		}
		else {
			beingAttacked->colision(org);
		}
	}
	for (int i = 0; i < _organismsNumberBeforeNextTurn; i++) {
		org = _organisms[i];
		org->setAge(org->getAge() + 1);
	}
	if (_isPlayerAlive) {
		_player->setPlayerSkillTurn(_player->getPlayerSkillTurn() + 1);
		if (_player->isPlayerSkillActive() && _player->getPlayerSkillTurn() == 5) {
			_player->endPlayerSkill();
		}
	}
	_turn++;
}

Organism* World::getBoardPoint(int x, int y) const {
	if ((x > 0) && (x < (_n + 2)) && (y > 0) && (y < (_m + 2))) {
		return _board[y][x];
	}
	return nullptr;
}

void World::addOrganism(Organism* org) {
	string event;
	int lastId;
	if ((_organismsNumber < _n * _m) && (_board[org->getY()][org->getX()] == nullptr)) {
		_organisms[_organismsNumber] = org;
		_organismsNumber++;
		if (_organismsNumber > 1 && org->isAnimal()) {
			Organism* temp;
			int i = 0;
			while (i < _organismsNumber && _organisms[i]->Getinitiative() >= org->Getinitiative()) {
				i++;
			}
			for (int j = _organismsNumber - 2; j >= i; j--) {
				temp = _organisms[j];
				_organisms[j] = _organisms[j + 1];
				_organisms[j + 1] = temp;
			}
		}
		org->print();
		if (typeid(*org) == typeid(Player))
		{
			_isPlayerAlive = true;
			_player = dynamic_cast<Player*>(org);
		}
		lastId = this->getLastIdOrganismNumber();
		event = org->getName() + " (organism ID: " + to_string(lastId) + "): new organism has borned";
		org->setID(lastId);
		_lastIdOrganismNumber++;
		this->addEvent(event);
	}
	else if ((_organismsNumber < _n * _m) && (_board[org->getY()][org->getX()] != nullptr)) {
		delete org;
	}
	else if (_organismsNumber >= _n * _m) {
		event = "Board full!";
		this->addEvent(event);
	}
}

void World::deleteOrganism(Organism* org) {
	string event;
	Organism* temp;
	Organism* beingAttacked;
	bool haveRunAway = true;
	if (org == _player && _player->isPlayerSkillActive()) {
		_player->runAway();
		if (_player->getLastMove() == 0) {
			haveRunAway = false;
		}
		else {
			event = "Player run away";
			this->addEvent(event);
			beingAttacked = _board[org->getY()][org->getX()];
			if (beingAttacked == nullptr) {
				_player->print();
			}
			else {
				beingAttacked->colision(_player);
			}
		}
	}
	if (org != _player || !_player->isPlayerSkillActive() || !haveRunAway) {
		beingAttacked = _board[org->getY()][org->getX()];
		if (beingAttacked == org) {
			_board[org->getY()][org->getX()] = nullptr;
		}
		if (typeid(*org) == typeid(Player)) {
			_isPlayerAlive = false;
		}
		for (int i = 0; i < _organismsNumber; i++) {
			if (_organisms[i] == org) {
				_organisms[i] = nullptr;
				for (int j = i; j < _organismsNumber - 1; j++) {
					temp = _organisms[j];
					_organisms[j] = _organisms[j + 1];
					_organisms[j + 1] = temp;
				}
				i = _organismsNumber;
			}
		}
		_organismsNumber--;
		_organismsNumberBeforeNextTurn--;

		event = org->getName() + " (organism ID:" + to_string(org->getID()) + "): died";
		this->addEvent(event);
		delete org;
	}
}

void World::generateEmptySpaces(int x, int y, int* positionX, int* positionY, int* move, int* pointsNumber) {
	if (y - 1 != 0 && _board[y - 1][x] == nullptr) {
		positionX[*pointsNumber] = x;
		positionY[*pointsNumber] = y - 1;
		move[*pointsNumber] = UP;
		(*pointsNumber)++;
	}
	if (x + 1 != _n + 1 && _board[y][x + 1] == nullptr) {
		positionX[*pointsNumber] = x + 1;
		positionY[*pointsNumber] = y;
		move[*pointsNumber] = RIGHT;
		(*pointsNumber)++;
	}
	if (y + 1 != _m + 1 && _board[y + 1][x] == nullptr) {
		positionX[*pointsNumber] = x;
		positionY[*pointsNumber] = y + 1;
		move[*pointsNumber] = DOWN;
		(*pointsNumber)++;
	}
	if (x - 1 != 0 && _board[y][x - 1] == nullptr) {
		positionX[*pointsNumber] = x - 1;
		positionY[*pointsNumber] = y;
		move[*pointsNumber] = LEFT;
		(*pointsNumber)++;
	}
}

World::~World() {
	delete[] _organisms;
	delete _player;
	for (int i = 0; i < _m; i++) {
		for (int j = 0; j < _n; j++) {
			delete _board[i];
		}
	}
	delete[] _events;
}