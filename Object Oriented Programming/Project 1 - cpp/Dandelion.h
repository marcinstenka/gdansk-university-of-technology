
#include <iostream>
#include <string.h>

#include "Plant.h"

using namespace std;

class World;
class Organism;
class Plant;

class Dandelion : public Plant {
private:
	const char _symbol = 'D';
	const int _probability = 35;
public:
	Dandelion();
	Dandelion(int x, int y, World* World);
	char getSymbol() const override;
	string getName() const override;
	void action() override;
	void colision(Organism* attacker) override;
};
