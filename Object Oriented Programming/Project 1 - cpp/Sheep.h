#ifndef Sheep_Defined
#define Sheep_Defined

#include <iostream>
#include <string.h>
#include "Animal.h"

using namespace std;

class Sheep : public Animal
{
private:
	const char _symbol = 'S';
public:
	Sheep();
	Sheep(int x, int y, World* World);
	void setMove(char move) override;
	int getLastMove() const override;
	char getSymbol() const override;
	string getName() const override;
	void action() override;
	void colision(Organism* attacker) override;
};

#endif