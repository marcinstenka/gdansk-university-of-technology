#ifndef Plant_Defined
#define Plant_Defined

#include <iostream>
#include <string.h>

#include "Organism.h"

using namespace std;

class Plant : public Organism {
protected:
	Organism* createOrganism(int x, int y, World* World) override;
public:
	Plant();
	Plant(int strength, int x, int y, World* World);
	int getLastMove() const override;
	virtual char getSymbol() const = 0;
	virtual string getName() const = 0;
	string write() const override;
	void action() override;
	void colision(Organism* attacker) override;
	bool isAnimal() override;
	void eventKilling(Organism* beingAttacked) override;
	void setMove(char move) override;
	void goBack() override;
	void runAway() override;
};
#endif