#ifndef Grass_Defined
#define Grass_Defined

#include <iostream>
#include <string.h>
#include "Plant.h"

using namespace std;

class World;
class Organism;
class Plant;

class Grass : public Plant {
private:
	const char _symbol = 'G';
	const int _probability = 40;
public:
	Grass();
	Grass(int x, int y, World* World);
	char getSymbol() const override;
	string getName() const override;
	void action() override;
	void colision(Organism* attacker) override;
};
#endif