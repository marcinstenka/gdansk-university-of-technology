#ifndef Blueberry_Defined
#define Blueberry_Defined

#include <iostream>
#include <string.h>
#include "Plant.h"

using namespace std;

class World;
class Organism;
class Plant;

class Blueberry : public Plant {
private:
	const char _symbol = 'B';
	const int _probability = 15;
public:
	Blueberry();
	Blueberry(int x, int y, World* World);
	char getSymbol() const override;
	string getName() const override;
	void action() override;
	void colision(Organism* attacker) override;
};
#endif