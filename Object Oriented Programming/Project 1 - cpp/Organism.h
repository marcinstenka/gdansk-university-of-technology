#ifndef Organism_Defined
#define Organism_Defined

#include <iostream>
#include <string.h>

using namespace std;

class World;

class Organism {
protected:
	int _strength;
	int _initiative;
	int _x;
	int _y;
	int _age;
	int _ID;
	World* _World;
	virtual Organism* createOrganism(int x, int y, World* World) = 0;
public:
	Organism();
	Organism(int strength, int initiative, int x, int y, World* World);
	void setStrength(int strength);
	void setInitiative(int initiative);
	void setPosition(int x, int y);
	void setAge(int age);
	void setID(int ID);
	void SetWorld(World* World);
	virtual void setMove(char move) = 0;
	int getStrength() const;
	int Getinitiative() const;
	int getX() const;
	int getY() const;
	int getAge() const;
	int getID() const;
	World* GetWorld() const;
	virtual int getLastMove() const = 0;
	virtual char getSymbol() const = 0;
	virtual string getName() const = 0;
	virtual string write() const = 0;
	virtual void action() = 0;
	virtual void colision(Organism* attacker) = 0;
	void print();
	virtual void goBack() = 0;
	virtual void runAway() = 0;
	virtual bool isAnimal() = 0;
	virtual void eventKilling(Organism* beingAttacked) = 0;
};

#endif