#ifndef Player_Defined
#define Player_Defined

#include <iostream>
#include <string.h>
#include "Animal.h"

using namespace std;

class World;
class Organism;
class Animal;

class Player : public Animal
{
private:
	const char _symbol = 'X';
	bool _skillActive;
	int _activeSkillTurnNumber;
public:
	Player(int x, int y, World* World);
	void setMove(char move) override;
	void setIsPlayerSkillActive(bool skillActive);
	void setPlayerSkillTurn(int turns);
	int getLastMove() const override;
	bool isPlayerSkillActive() const;
	int getPlayerSkillTurn() const;
	char getSymbol() const override;
	string getName() const override;
	string write() const override;
	void action() override;
	void colision(Organism* attacker) override;
	void runAway() override;
	void activateSkill();
	void endPlayerSkill();
};
#endif