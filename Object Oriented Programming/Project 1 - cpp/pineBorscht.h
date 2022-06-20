#ifndef pineBorscht_Defined
#define pineBorscht_Defined

#include <iostream>
#include <string.h>
#include "Plant.h"

using namespace std;

class World;
class Organism;
class Plant;

class pineBorscht : public Plant {
private:
	const char _symbol = 'P';
	const int _probability = 10;
public:
	pineBorscht();
	pineBorscht(int x, int y, World* World);
	char getSymbol() const override;
	string getName() const override;
	void action() override;
	void colision(Organism* attacker) override;
};
#endif