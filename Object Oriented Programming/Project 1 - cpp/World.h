#ifndef World_Defined
#define World_Defined

#include <iostream>
#include <string.h>

using namespace std;

class Organism;
class Player;

class World {
private:
	Organism** _organisms;
	Player* _player;
	int _organismsNumber;
	int _organismsNumberBeforeNextTurn;
	Organism*** _board;
	int _n;
	int _m;
	int _turn;
	bool _isPlayerAlive;
	int _lastIdOrganismNumber;
	string* _events;
	int _eventsNumber;
	void doActions();
public:
	World();
	World(int n, int m);
	void setBoardSize(int n, int m);
	void putOrganismOnPoint(int x, int y, Organism* org);
	void setTurn(int turn);
	void addEvent(string event);
	int getN() const;
	int getM() const;
	int getOrganismsNumber() const;
	int getTurn() const;
	int getLastIdOrganismNumber() const;
	Organism* getBoardPoint(int x, int y) const;
	Organism* getOrganism(int i) const;
	Player* getPlayer() const;
	void addOrganism(Organism* org);
	void deleteOrganism(Organism* org);
	void generateEmptySpaces(int x, int y, int* positionX, int* positionY, int* move, int* pointsNumber);
	void takeTurn();
	void printWorld();
	~World();
};
#endif;