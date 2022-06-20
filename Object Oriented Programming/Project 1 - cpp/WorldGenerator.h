
#include <iostream>
#include <string.h>

using namespace std;

class World;

class WorldGenerator {
private:
	World* _World;
	void generatePointsForOrganisms(int* points, int* AnimalsPerSpiecesNumber);
	void readPointCoords(int* points, int* x, int* y, int* whichPoint);
	void loadOrganism(string name, int strength, int initiative, int x, int y, int age);
public:
	WorldGenerator(World* World);
	void generateWorld();
	bool loadWorld();
	void saveWorld();
	~WorldGenerator();
};
