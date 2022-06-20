#include <fstream>
#include <string>
#include <Windows.h>

#include "World.h"
#include "WorldGenerator.h"

#include "Organism.h"
#include "Grass.h"
#include "Player.h"
#include "Wolf.h"
#include "Sheep.h"
#include "Fox.h"
#include "Turtle.h"
#include "Antelope.h"
#include "Dandelion.h"
#include "Guarana.h"
#include "Blueberry.h"
#include "pineBorscht.h"

#define ALL_SPIECES_NUMBER 10
#define FREE_SPACE_NUMBER 20
#define WOLF "Wolf"
#define SHEEP "Sheep"
#define FOX "Fox"
#define TURTLE "Turtle"
#define ANTELOPE "Antelope"
#define GRASS "Grass"
#define DANDELION "Dandelion"
#define GUARANA "Guarana"
#define BORSCHT "Borscht"
#define BLUEBERRY "Blueberry"
#define PLAYER "Player"

using namespace std;

WorldGenerator::WorldGenerator(World* World) {
	_World = World;
}

void WorldGenerator::generateWorld() {
	int n = _World->getN();
	int m = _World->getM();
	int AnimalsPerSpicesNumber = n * m / (ALL_SPIECES_NUMBER + FREE_SPACE_NUMBER);
	int* pointsTaken = new int[AnimalsPerSpicesNumber * ALL_SPIECES_NUMBER + 1];
	this->generatePointsForOrganisms(pointsTaken, &AnimalsPerSpicesNumber);
	int i = 0;
	int x = pointsTaken[i] % n;
	int y = (pointsTaken[i] - x) / n;
	Organism* player = new Player(x, y, _World);
	_World->addOrganism(player);

	for (int i = 0; i < AnimalsPerSpicesNumber; i++) {
		readPointCoords(pointsTaken, &x, &y, &i);
		Organism* wolf = new Wolf(x, y, _World);
		_World->addOrganism(wolf);

		readPointCoords(pointsTaken, &x, &y, &i);
		Organism* sheep = new Sheep(x, y, _World);
		_World->addOrganism(sheep);

		readPointCoords(pointsTaken, &x, &y, &i);
		Organism* fox = new Fox(x, y, _World);
		_World->addOrganism(fox);

		readPointCoords(pointsTaken, &x, &y, &i);
		Organism* turtle = new Turtle(x, y, _World);
		_World->addOrganism(turtle);

		readPointCoords(pointsTaken, &x, &y, &i);
		Organism* antelope = new Antelope(x, y, _World);
		_World->addOrganism(antelope);

		readPointCoords(pointsTaken, &x, &y, &i);
		Organism* grass = new Grass(x, y, _World);
		_World->addOrganism(grass);

		readPointCoords(pointsTaken, &x, &y, &i);
		Organism* dandelion = new Dandelion(x, y, _World);
		_World->addOrganism(dandelion);

		readPointCoords(pointsTaken, &x, &y, &i);
		Organism* guarana = new Guarana(x, y, _World);
		_World->addOrganism(guarana);

		readPointCoords(pointsTaken, &x, &y, &i);
		Organism* blueberry = new Blueberry(x, y, _World);
		_World->addOrganism(blueberry);

		readPointCoords(pointsTaken, &x, &y, &i);
		Organism* borsch = new pineBorscht(x, y, _World);
		_World->addOrganism(borsch);
	}
}

bool WorldGenerator::loadWorld() {
	bool result = true;
	const string file = "file.txt";
	ifstream loadStream(file.c_str());
	if (loadStream.good()) {
		int n, m, turn, organismsNumber;
		loadStream >> n >> m >> turn >> organismsNumber;
		_World->setBoardSize(n, m);
		_World->setTurn(turn);
		string name, name2;
		int strength, initiative, x, y, age, skillActive, turnsWithSkillActive;
		bool isSkillActive;
		for (int i = 0; i < organismsNumber; i++) {
			loadStream >> name;
			if (name == BLUEBERRY || name == BORSCHT) {
				loadStream >> name2;
				name += " " + name2;
			}
			loadStream >> strength >> initiative >> x >> y >> age;
			if (name == PLAYER) {
				loadStream >> skillActive >> turnsWithSkillActive;
				Organism* org = new Player(x - 1, y - 1, _World);
				org->setStrength(strength);
				org->setInitiative(initiative);
				org->setAge(age);
				if (skillActive == 0) {
					isSkillActive = false;
				}
				else {
					isSkillActive = true;
				}
				_World->addOrganism(org);
				_World->getPlayer()->setIsPlayerSkillActive(isSkillActive);
				_World->getPlayer()->setPlayerSkillTurn(turnsWithSkillActive);
			}
			else {
				loadOrganism(name, strength, initiative, x - 1, y - 1, age);
			}
		}
		loadStream.close();
	}
	else {
		cout << "file.txt not found - there must be file.txt to load game." << endl;
		result = false;
	}
	Sleep(1000);
	return result;
}

void WorldGenerator::saveWorld() {
	ofstream saveStream("file.txt");
	int organismsNumber = _World->getOrganismsNumber();
	saveStream << _World->getN() << " " << _World->getM() << " " << _World->getTurn() << " " << organismsNumber << endl;
	Organism* org = nullptr;
	for (int i = 0; i < organismsNumber; i++) {
		org = _World->getOrganism(i);
		saveStream << org->write() << endl;
	}
	saveStream.close();
	cout << "Game saved" << endl;
}

void WorldGenerator::generatePointsForOrganisms(int* points, int* AnimalsPerSpiecesNumber) {
	int n = _World->getN();
	int m = _World->getM();
	int howManyPointsNeeded = (*AnimalsPerSpiecesNumber) * ALL_SPIECES_NUMBER + 1;
	int* allPoints = new int[n * m];
	int randomNumber;
	for (int i = 0; i < n * m; i++) {
		allPoints[i] = 0;
	}
	for (int i = 0; i < howManyPointsNeeded; i++) {
		do {
			randomNumber = rand() % (n * m);
		} while (allPoints[randomNumber] == 1);
		allPoints[randomNumber] = 1;
		points[i] = randomNumber;
	}
}

void WorldGenerator::readPointCoords(int* points, int* x, int* y, int* whichPoint) {
	int n = _World->getN();
	*x = points[*whichPoint] % n;
	*y = (points[*whichPoint] - *x) / n;
	(*whichPoint)++;
}

void WorldGenerator::loadOrganism(string name, int strength, int initiative, int x, int y, int age) {
	Organism* org = nullptr;
	if (name == WOLF) {
		org = new Wolf(x, y, _World);
	}
	else if (name == SHEEP) {
		org = new Sheep(x, y, _World);
	}
	else if (name == FOX) {
		org = new Fox(x, y, _World);
	}
	else if (name == TURTLE) {
		org = new Turtle(x, y, _World);
	}
	else if (name == ANTELOPE) {
		org = new Antelope(x, y, _World);
	}
	else if (name == GRASS) {
		org = new Grass(x, y, _World);
	}
	else if (name == DANDELION) {
		org = new Dandelion(x, y, _World);
	}
	else if (name == GUARANA) {
		org = new Guarana(x, y, _World);
	}
	else if (name == BORSCHT) {
		org = new pineBorscht(x, y, _World);
	}
	else if (name == BLUEBERRY) {
		org = new Blueberry(x, y, _World);
	}
	if (org != nullptr) {
		org->setStrength(strength);
		org->setInitiative(initiative);
		org->setAge(age);
		_World->addOrganism(org);
	}
}

WorldGenerator::~WorldGenerator() {
	delete _World;
}