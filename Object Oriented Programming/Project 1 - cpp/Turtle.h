#ifndef Turtle_Defined
#define Turtle_Defined

#include <iostream>
#include <string.h>
#include "Animal.h"

using namespace std;

class World;
class Organism;
class Animal;

class Turtle : public Animal {
private:
	const char _symbol = 'T';
public:
	Turtle();
	Turtle(int x, int y, World* World);
	void setMove(char move) override;
	int getLastMove() const override;
	char getSymbol() const override;
	string getName() const override;
	void action() override;
	void colision(Organism* attacker) override;
};
#endif