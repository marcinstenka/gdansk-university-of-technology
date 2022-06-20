#ifndef Animal_Defined
#define Animal_Defined

#include <iostream>
#include <string.h>

#include "Organism.h"

using namespace std;

class World;
class Organism;

class Animal : public Organism
{
private:
	void breed(Organism* beingAttacked, World* World);
	Organism* createOrganism(int x, int y, World* World) override;
protected:
	int _lastMove;
	void moveToEmptyField();
	void moveSeveralTimes(int length);
public:
	Animal();
	Animal(int strength, int initiative, int x, int y, World* World);
	void action() override;
	void colision(Organism* attacker) override;
	void setMove(char move) override;
	int getLastMove() const override;
	virtual char getSymbol() const = 0;
	virtual string getName() const = 0;
	string write() const override;
	void goBack() override;
	void runAway() override;
	bool isAnimal() override;
	void eventKilling(Organism* beingAttacked) override;
};
#endif