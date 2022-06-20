
#include <iostream>
#include <string.h>
#include "Animal.h"

using namespace std;

class World;
class Organism;
class Animal;

class Wolf : public Animal {
private:
	const char _symbol = 'W';
public:
	Wolf();
	Wolf(int x, int y, World* World);
	void setMove(char move) override;
	int getLastMove() const override;
	char getSymbol() const override;
	string getName() const override;
	void action() override;
	void colision(Organism* attacker) override;
};
