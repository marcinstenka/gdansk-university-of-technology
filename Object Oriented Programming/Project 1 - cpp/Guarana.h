#ifndef Guarana_Defined
#define Guarana_Defined

#include <iostream>
#include <string.h>
#include "Plant.h"

using namespace std;

class World;
class Organism;
class Plant;

class Guarana : public Plant {
private:
	const char _symbol = 'U';
	const int _probability = 20;
public:
	Guarana();
	Guarana(int x, int y, World* World);
	char getSymbol() const override;
	string getName() const override;
	void action() override;
	void colision(Organism* attacker) override;
};

#endif