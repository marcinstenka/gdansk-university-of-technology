#include <iostream>
#include <conio.h>
#include <string>
#include <time.h>

#include "WorldGenerator.h"
#include "World.h"

#define CHAR_KEYS 224
#define SPACE_KEY 32
#define SAVE 115
#define READ 108
#define NEW 110
#define ALL_SPIECES_NUMBER 10
#define FREE_SPACE_NUMBER 20			
#define INVALID_OPERATION "Invalid operation!"			
#define SET_BOARD "Set board size (for example: 20 20): "			
#define NEW_GAME "New game"			

using namespace std;

int main() {
	srand(time(NULL));
	int n, m;
	char instruction1 = NULL;
	char instruction2 = NULL;
	bool isLoaded = true;
	cout << "press n or l key" << endl;
	cout << "n - new game" << endl;
	cout << "l - load game" << endl;

	World* world = nullptr;
	WorldGenerator* generator = nullptr;

	do {
		isLoaded = true;
		instruction1 = _getch();
		switch (instruction1) {
		case READ:
			world = new World();
			generator = new WorldGenerator(world);
			if (!generator->loadWorld()) {
				cout << INVALID_OPERATION << endl;
				isLoaded = false;
			}
			break;
		case NEW:
			do {
				cout << SET_BOARD;
				cin >> n >> m;
				system("cls");
			} while (n * m < (ALL_SPIECES_NUMBER + FREE_SPACE_NUMBER));

			world = new World(n, m);
			generator = new WorldGenerator(world);
			generator->generateWorld();
			break;
		default:
			cout << INVALID_OPERATION << endl;
		}
	} while ((instruction1 != READ || !isLoaded) && instruction1 != NEW);
	system("cls");
	world->printWorld();
	do {
		instruction2 = _getch();
		switch (instruction2) {
		case SAVE:
			generator->saveWorld();
			break;
		case SPACE_KEY:
			world->takeTurn();
			system("cls");
			world->printWorld();
			break;
		case NEW:
			system("cls");
			cout << NEW_GAME << endl << endl;
			do {
				cout << SET_BOARD;
				cin >> n >> m;
				system("cls");
			} while (n * m < (ALL_SPIECES_NUMBER + FREE_SPACE_NUMBER));

			world = new World(n, m);
			generator = new WorldGenerator(world);
			generator->generateWorld();
			system("cls");
			world->printWorld();
			break;
		default:
			cout << INVALID_OPERATION << endl;
		}
	} while (true);
	delete generator;
	delete world;
	return 0;
}