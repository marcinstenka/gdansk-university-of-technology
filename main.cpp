#include <iostream>
#include <stdlib.h>
#define BOARD_Y 21
#define BOARD_X 10
#define DEFAULT_Y1_A 0;
#define DEFAULT_Y2_A 9;
#define DEFAULT_Y1_B 11;
#define DEFAULT_Y2_B 20;
#define DEFAULT_X1 0;
#define DEFAULT_X2 9;
#define PLAYER_NAME_SIZE 9
#define N 'N'
#define S 'S'
#define E 'E'
#define W 'W'
#define F 'F'
#define R 'R'
#define L 'L'
#define SHIP_TYPE_LENGTH 4
#define MAX_SHIP_SEGMENTS 6
#define DEFAULT_CAR_Q 1
#define DEFAULT_BAT_Q 2
#define DEFAULT_CRU_Q 3
#define DEFAULT_DES_Q 4
#define MAX_SHIPS_Q 10
#define SHIP_TYPES 4
#define CAN_SHOOT 0
#define CAN_MOVE 1
#define CAN_SEE 2
#define SHIP_TYPES 4
#define CAR 0
#define BAT 1
#define CRU 2
#define DES 3
#define INPUT_SIZE 20
#define NOT_IN_STARTING_POSITION "NOT IN STARTING POSITION"
#define SHIP_ALREADY_PRESENT "SHIP ALREADY PRESENT"
#define ALL_SHIPS_OF_THE_CLASS_ALREADY_SET "ALL SHIPS OF THE CLASS ALREADY SET"
#define THE_OTHER_PLAYER_EXPECTED "THE OTHER PLAYER EXPECTED"
#define NOT_ALL_SHIPS_PLACED "NOT ALL SHIPS PLACED"
#define PLACING_SHIP_TOO_CLOSE_TO_OTHER_SHIP "PLACING SHIP TOO CLOSE TO OTHER SHIP"
#define FIELD_DOES_NOT_EXIST "FIELD DOES NOT EXIST"
#define REEF_IS_NOT_PLACED_ON_BOARD "REEF IS NOT ON BOARD"
#define PLACING_SHIP_ON_REEF "PLACING SHIP ON REEF"
#define SHIP_MOVED_ALREADY "SHIP MOVED ALREADY"
#define SHIP_WENT_FROM_BOARD "SHIP WENT FROM BOARD"
#define SHIP_CANNOT_MOVE "SHIP CANNOT MOVE"
#define SHIP_CANNOT_SHOOT "SHIP CANNOT SHOOT"
#define TOO_MANY_SHOOTS "TOO MANY SHOOTS"
#define SHOOTING_TOO_FAR "SHOOTING TOO FAR"
#define STATE 1
#define PLAYER_A 2
#define PLAYER_B 3
#define PRINT 4
#define SET_FLEET 5 
#define NEXT_PLAYER 6
#define REEF 7
#define BOARD_SIZE 8
#define INIT_POSITION 9
#define SHIP 10
#define PLACE_SHIP 11
#define SHOOT 12
#define MOVE 13
#define EXTENDED_SHIPS 14
#define SAVE 15

using namespace std;

struct gameOptions {
	int boardY = BOARD_Y;
	int boardX = BOARD_X;
	char nextPlayer = 'A';
	bool extended = false;
};
struct shipStruct {
	 bool isSetOnBoard = false;
	 bool isDefined = false;
	 char direction;
	 int possibleMoves = 3;
	 int possibleShots;
	 int yHead;
	 int xHead;
	 int shipLength;
	 char specialSegments[MAX_SHIP_SEGMENTS]= "";
	 char segments[MAX_SHIP_SEGMENTS]= "";
	 bool functionality[3] = {true, true, true};
 };

  struct PLAYER {
	char name[PLAYER_NAME_SIZE];
	shipStruct ships[SHIP_TYPES][MAX_SHIPS_Q];
	int shipsQuantity = MAX_SHIPS_Q;
	int parts_remaining = 0;
	int y1;
	int y2;
	int x1 = DEFAULT_X1;
	int x2 = DEFAULT_X2;
};

//general functions
  int makeTask(char order[INPUT_SIZE]);
  int makeStateTask(char stateOrder[INPUT_SIZE]);
  int makePlayerTask(char playerOrder[INPUT_SIZE], char playerName[PLAYER_NAME_SIZE]);
  void manageState(gameOptions* game, char** board, int* yBoard, int* xBoard, PLAYER* player_A, PLAYER* player_B);
  void mangePlayer(gameOptions* game, char**& board, int* yBoard, int* xBoard, PLAYER* activePlayer, PLAYER* secondPlayer, char currentPlayer);
  void initializeGame(char** board, PLAYER* player_A, PLAYER* player_B);
  void save_player(PLAYER* player);
  void resetShips(PLAYER* player);
 //commands functions
  void place_ship(char** board, int* yBoard, int* xBoard, PLAYER* player);
  void ship(char**& board, int* yBoard, int* xBoard, PLAYER* player);
  void move(char** board, int* yBoard, int* xBoard, PLAYER* player);
  void set_fleet(PLAYER* player);
  void shoot(char**& board, int* yBoard, int* xBoard, PLAYER* activePlayer, PLAYER* secondPlayer);
  void shoot_extended(char**& board, int* yBoard, int* xBoard, PLAYER* activePlayer, PLAYER* secondPlayer);
  void reef(char**& board, int* yBoard, int* xBoard);
  void init_position(PLAYER* player);
  void next_player(gameOptions* game);
  void print(char** board, int* yBoard, int* xBoard, PLAYER* player_A, PLAYER* player_B);
  void board_size(char**& board, int* ySize, int* xSize);
  void save(gameOptions* game, char** board, PLAYER* player_A, PLAYER* player_B);
//functions used by commands functions
  bool isOutOfBoard(int* yBoard, int* xBoard, PLAYER* player, int whichShip, char shipType[SHIP_TYPE_LENGTH], char moveDirection);
  void checkIsOutOfBoardF(int* yBoard, int* xBoard, PLAYER* player, int whichShip, char shipType[SHIP_TYPE_LENGTH], char moveDirection);
  void checkIsOutOfBoardRorL(int* yBoard, int* xBoard, PLAYER* player, int whichShip, char shipType[SHIP_TYPE_LENGTH], char moveDirection, char RorL);
  bool isTooClose(char** board, int* yBoard, int* xBoard, int y, int x, int direction, int shipLength);
  bool checkIsTooCloseF(char**& board, int* yBoard, int* xBoard, PLAYER* player, int shipTypeArrayId, int whichShip, int shipLength);
  bool checkIsTooCloseRorL(char**& board, int* yBoard, int* xBoard, PLAYER* player, int shipTypeArrayId, int whichShip, int shipLength, char RorL);
  bool isMovedTooClose(char** board, int* yBoard, int* xBoard, PLAYER* player, int whichShip, char shipType[SHIP_TYPE_LENGTH], char moveDirection);
  void changeDirection(PLAYER* player, int shipTypeArrayId, int whichShip, char RorL, char direction);

  void checkIsReefRorL(char** board, PLAYER* player, int shipTypeArrayId, int whichShip, char shipType[SHIP_TYPE_LENGTH], int shipLength, char moveDirection, char RorL);
  void checkIsReefFandMoveShip(char**& board, PLAYER* player, int shipTypeArrayId, int whichShip, char shipType[SHIP_TYPE_LENGTH], int shipLength, char moveDirection);
  void isReefAndDoMove(char** board, PLAYER* player, int whichShip, char shipType[SHIP_TYPE_LENGTH], char moveDirection);
  bool isReef(char**& board, int y, int x, char direction, int whichShip, char shipType[SHIP_TYPE_LENGTH], int shipLength);

  void makeShot(PLAYER* player, int y, int x);
  int* getCannonPosition(PLAYER* player, int shipTypeArrayId, int whichShip);
  char* hideShipTemporary(char**& board, int y, int x, char direction, int shipLength);
  void showShipTemporary(char**& board, int y, int x, char direction, int shipLength, char* shipSegments);

  void dockShip(char**& board, int y, int x, char direction, int shipLenght, char shipSegments[MAX_SHIP_SEGMENTS]);
  void moveShip(char**& board, int y, int x, int newY, int newX, char direction, char RorL);

  bool isPlaceInInitialPosition(PLAYER* player, int y, int x, char direction, int whichShip, char shipType[SHIP_TYPE_LENGTH], int shipLength);
  bool isShipSetOnBoard(PLAYER* player, int y, int x, char direction, char shipType[SHIP_TYPE_LENGTH], int shipTypeArrayId, int whichShip);
  bool isShipDefined(PLAYER* player, int y, int x, char direction, char shipType[SHIP_TYPE_LENGTH], int shipTypeArrayId, int whichShip);
  char printSegments(PLAYER* player, char**& board, int y, int x);
  void setShipSegments(char**& board, char shipSegments[MAX_SHIP_SEGMENTS], int y, int x, char direction, int i, int j);
  void setSectionsOfShip(PLAYER* player, int shipTypeArrayId, int whichShip, int shipLength, char shipSegments[MAX_SHIP_SEGMENTS]);
  bool areAllShipsPlaced(PLAYER* player);

  int measureShip(char shipType[SHIP_TYPE_LENGTH]);
  int getShipTypeArrayId(char shipType[SHIP_TYPE_LENGTH]);
  char checkWhichPlayer(PLAYER* player);
  char whichPlayerInState();

int main() {
	gameOptions gameSettings;
	gameOptions* game = &gameSettings;
	char** board = (char**)malloc(BOARD_Y * BOARD_X * sizeof(char));
	for (int i = 0; i < BOARD_Y; i++) {
		board[i] = (char*)malloc(BOARD_X * sizeof(char));
	}
	char currentPlayer = 'A';
	PLAYER playerA, playerB;
	PLAYER* player_A = &playerA;
	PLAYER* player_B = &playerB;

	int y = BOARD_Y;
	int x = BOARD_X;
	int* yBoard = &y;
	int* xBoard = &x;
	initializeGame(board, player_A, player_B);
	char order[INPUT_SIZE];

	while (cin >> order) {
		int task = 0;
		task = makeTask(order);
		switch (task) {
		case STATE:
			manageState(game, board, yBoard, xBoard, player_A, player_B);
			break;
		case PLAYER_A:
			mangePlayer(game, board, yBoard, xBoard, player_A, player_B, currentPlayer);
			resetShips(player_A);
			currentPlayer = 'B';
			break;
		case PLAYER_B:
			mangePlayer(game, board, yBoard, xBoard, player_B, player_A, currentPlayer);
			resetShips(player_B);
			currentPlayer = 'A';
			break;
		default:
			break;
		}
	}
	return 0;
}

int makeTask(char order[INPUT_SIZE]) {
	if (!strcmp(order, "[state]")) {
		return 1;
	}
	else if (!strcmp(order, "[playerA]")) {
		return 2;
	}
	else if (!strcmp(order, "[playerB]")) {
		return 3;
	}
	return 0;
}

int makeStateTask(char stateOrder[INPUT_SIZE]) {
	if (!strcmp(stateOrder, "[state]")) {
		return STATE;
	}
	else if (!strcmp(stateOrder, "PRINT")) {
		return PRINT;
	}
	else if (!strcmp(stateOrder, "SET_FLEET")) {
		return SET_FLEET;
	}
	else if (!strcmp(stateOrder, "NEXT_PLAYER")) {
		return NEXT_PLAYER;
	}
	else if (!strcmp(stateOrder, "REEF")) {
		return REEF;
	}
	else if (!strcmp(stateOrder, "BOARD_SIZE")) {
		return BOARD_SIZE;
	}
	else if (!strcmp(stateOrder, "INIT_POSITION")) {
		return INIT_POSITION;
	}
	else if (!strcmp(stateOrder, "SHIP")) {
		return SHIP;
	}
	else if (!strcmp(stateOrder, "EXTENDED_SHIPS")) {
		return EXTENDED_SHIPS;
	}
	else if (!strcmp(stateOrder, "SAVE")) {
		return SAVE;
	}
	return 0;
}

int makePlayerTask(char playerOrder[INPUT_SIZE], char playerName[PLAYER_NAME_SIZE]) {
	if (!strcmp(playerName, "PLAYER_A")) {
		if (!strcmp(playerOrder, "[playerA]")) {
			return PLAYER_A;
		}
	}
	else if (!strcmp(playerName, "PLAYER_B")) {
		if (!strcmp(playerOrder, "[playerB]")) {
			return PLAYER_B;
		}
	}
	if (!strcmp(playerOrder, "PLACE_SHIP")) {
		return PLACE_SHIP;
	}
	else if (!strcmp(playerOrder, "SHOOT")) {
		return SHOOT;
	}
	else if (!strcmp(playerOrder, "MOVE")) {
		return MOVE;
	}
	return 0;
}

int measureShip(char shipType[SHIP_TYPE_LENGTH]) {
	if (!strcmp(shipType, "CAR")) {
		return 5;
	}
	else if (!strcmp(shipType, "BAT")) {
		return 4;
	}
	else if (!strcmp(shipType, "CRU")) {
		return 3;
	}
	else if (!strcmp(shipType, "DES")) {
		return 2;
	}
	return 0;
}

void init_position(PLAYER* player) {
	int y1, x1, y2, x2;
	cin >> y1; cin >> x1; cin >> y2; cin >> x2;
	player->y1 = y1;
	player->x1 = x1;
	player->y2 = y2;
	player->x2 = x2;
}

int getShipTypeArrayId(char shipType[SHIP_TYPE_LENGTH]) {
	if (!strcmp(shipType, "CAR")) {
		return CAR;
	}
	else if (!strcmp(shipType, "BAT")) {
		return BAT;
	}
	else if (!strcmp(shipType, "CRU")) {
		return CRU;
	}
	else if (!strcmp(shipType, "DES")) {
		return DES;
	}
	return NULL;
}

char checkWhichPlayer(PLAYER* player) {
	if (!strcmp(player->name, "PLAYER_A")) {
		return 'A';
	}
	else {
		return 'B';
	}
}

char whichPlayerInState() {
	char name;
	cin >> name;
	return name;
}

char printSegments(PLAYER* player, char** &board, int y, int x) {
	for (int i = 0; i < SHIP_TYPES; i++) {
		for (int j = 0; j < MAX_SHIPS_Q; j++) {
			char direction = player->ships[i][j].direction;
			if (player->ships[i][j].isDefined) {
				int yHead = player->ships[i][j].yHead;
				int xHead = player->ships[i][j].xHead;
				int shipLength = player->ships[i][j].shipLength;
				int l = 0;
				switch (direction) {
				case N:
					for (int k = yHead; k <= yHead + shipLength; k++) {
						if (k == y && xHead == x) {
							if (player->ships[i][j].specialSegments[l] == '@') {
								return '@';
							}
							if (player->ships[i][j].specialSegments[l] == '!') {
								return '!';
							}
							if (player->ships[i][j].specialSegments[l] == '%') {
								return '%';
							}
						}
						l++;
					}
					break;
				case S:
					for (int k = yHead; k >= yHead - shipLength; k--) {
						if (k == y && xHead == x) {
							if (player->ships[i][j].specialSegments[l] == '@') {
								return '@';
							}
							if (player->ships[i][j].specialSegments[l] == '!') {
								return '!';
							}
							if (player->ships[i][j].specialSegments[l] == '%') {
								return '%';
							}
						}
						l++;
					}
					break;
				case E:
					for (int k = xHead; k >= xHead - shipLength; k--) {
						if (k == x && yHead == y) {
							if (player->ships[i][j].specialSegments[l] == '@') {
								return '@';
							}
							if (player->ships[i][j].specialSegments[l] == '!') {
								return '!';
							}
							if (player->ships[i][j].specialSegments[l] == '%') {
								return '%';
							}
						}
						l++;
					}
					break;
				case W:
					for (int k = xHead; k <= xHead + shipLength; k++) {
						if (k == x && yHead == y) {
							if (player->ships[i][j].specialSegments[l] == '@') {
								return '@';
							}
							if (player->ships[i][j].specialSegments[l] == '!') {
								return '!';
							}
							if (player->ships[i][j].specialSegments[l] == '%') {
								return '%';
							}
						}
						l++;
					}
					break;
				}
			}

		}
	}
	return ' ';
}

void print(char** board, int* yBoard, int* xBoard, PLAYER* player_A, PLAYER* player_B) {
	int x = 0;
	cin >> x;
	if (x == 0) {
		for (int i = 0; i < *yBoard; i++) {
			for (int j = 0; j < *xBoard; j++) {
				cout << board[i][j];
			}
			cout << endl;
		}
	}
	if (x == 1) {
		int yCounter = 0;
		int additionalZeroesY = 0;
		int additionalZeroesX = 0;
		
		int howManyDigitsY = floor(log10(abs(*yBoard))) + 1;
		int howManyZeroesY = howManyDigitsY - 1;
		//X nums
		while (*yBoard / pow(10, additionalZeroesX) > 10) {
			additionalZeroesX++;
		}
		while (*xBoard / pow(10, additionalZeroesY) > 10) {
			additionalZeroesY++;
		}
		for (int i = additionalZeroesY; i >= 0; i--) {
			for (int j = 0; j <= additionalZeroesX; j++) {
				cout << ' ';
			}
			if (i != 0) {
				for (int j = 0; j < *xBoard; j++) {
					cout << j / (int)pow(10, i);
				}
			}
			else {
				for (int j = 0; j < *xBoard; j++) {
					cout << j % 10;
				}
			}
			cout << endl;
		}
		// Y nums
		for (int i = 0; i < *yBoard; i++) {
			for (int j = 0; j < *xBoard; j++) {
				if (j == 0) {
					for (int k = 0; k < howManyZeroesY; k++) {
						cout << 0;
					}
					cout << yCounter;
					yCounter++;
					if (yCounter % 10 == 0) {
						howManyZeroesY--;
					}
				} if (j < *xBoard && i < *yBoard) {
					char shipSegment;
					if (board[i][j] == 'x') {
						cout << board[i][j];
					}
					else {
						shipSegment = printSegments(player_A, board, i, j);
						if (shipSegment == ' ') {
							shipSegment = printSegments(player_B, board, i, j);
						}
						if (shipSegment == '@' || shipSegment == '!' || shipSegment == '%') {
							cout << shipSegment;
						}
						else {
							cout << board[i][j];
						}
					}
				}
			}
			cout << endl;
		}
	}
	cout << "PARTS REMAINING:: A : " << player_A->parts_remaining << " B : " << player_B->parts_remaining << endl;
}

void set_fleet(PLAYER* player) {
	int CARquantity, BATquantity, CRUquantity, DESquantity;
	cin >> CARquantity;
	cin >> BATquantity;
	cin >> CRUquantity;
	cin >> DESquantity;
	//clear ships that are defined by default
	for (int i = 0; i < SHIP_TYPES; i++) {
		for (int j = 0; j < MAX_SHIPS_Q - 1; j++) {
			player->ships[i][j].isDefined = false;
		}
	}
	for (int i = 0; i < SHIP_TYPES; i++) {
		for (int j = 0; j < CARquantity; j++) {
			player->ships[i][j].isDefined = true;
			player->ships[i][j].possibleMoves = 2;
			player->ships[i][j].shipLength = 5;
		}
		i++;
		for (int j = 0; j < BATquantity; j++) {
			player->ships[i][j].isDefined = true;
			player->ships[i][j].possibleMoves = 3;
			player->ships[i][j].shipLength = 4;
		}
		i++;
		for (int j = 0; j < CRUquantity; j++) {
			player->ships[i][j].isDefined = true;
			player->ships[i][j].possibleMoves = 3;
			player->ships[i][j].shipLength = 3;
		}
		i++;
		for (int j = 0; j < DESquantity; j++) {
			player->ships[i][j].isDefined = true;
			player->ships[i][j].possibleMoves = 3;
			player->ships[i][j].shipLength = 2;
		}
	}
	player->shipsQuantity = CARquantity + BATquantity + CRUquantity + DESquantity;
}

bool isReef(char**& board, int y, int x, char direction, int whichShip, char shipType[SHIP_TYPE_LENGTH], int shipLength) {
	if (board[y][x] == ' ') {
		switch (direction) {
		case S:
			for (int i = y - (shipLength - 1); i <= y; i++) {
				if (board[i][x] == '#') {
					printf_s("INVALID OPERATION \"PLACE_SHIP %d %d %c %d %s\": %s\n", y, x, direction, whichShip, shipType, PLACING_SHIP_ON_REEF);
					exit(0);
				}
			}
			return true;
		case N:
			for (int i = y + (shipLength - 1); i >= y; i--) {
				if (board[i][x] == '#') {
					printf_s("INVALID OPERATION \"PLACE_SHIP %d %d %c %d %s\": %s\n", y, x, direction, whichShip, shipType, PLACING_SHIP_ON_REEF);
					exit(0);
				}
			}
			return true;
		case W:
			for (int i = x + (shipLength - 1); i >= x; i--) {
				if (board[y][i] == '#') {
					printf_s("INVALID OPERATION \"PLACE_SHIP %d %d %c %d %s\": %s\n", y, x, direction, whichShip, shipType, PLACING_SHIP_ON_REEF);
					exit(0);
				}
			}
			return true;
		case E:
			for (int i = x - (shipLength - 1); i <= x; i++) {
				if (board[y][i] == '#') {
					printf_s("INVALID OPERATION \"PLACE_SHIP %d %d %c %d %s\": %s\n", y, x, direction, whichShip, shipType, PLACING_SHIP_ON_REEF);
					exit(0);
				}
			}
			return true;
		}
	}
	printf_s("INVALID OPERATION \"PLACE_SHIP %d %d %c %d %s\": %s\n", y, x, direction, whichShip, shipType, PLACING_SHIP_ON_REEF);
	exit(0);
}

bool isPlaceInInitialPosition(PLAYER* player, int y, int x, char direction, int whichShip, char shipType[SHIP_TYPE_LENGTH], int shipLength) {
	if ((y >= player->y1) && (y <= player->y2) && (x >= player->x1) && (x <= player->x2)) {
		switch (direction) {
		case S:
			if (y - (shipLength - 1) < player->y1) {
				printf_s("INVALID OPERATION \"PLACE_SHIP %d %d %c %d %s\": %s\n", y, x, direction, whichShip, shipType, NOT_IN_STARTING_POSITION);
				exit(0);
			}
			return true;
		case N:
			if (y + (shipLength - 1) > player->y2) {
				printf_s("INVALID OPERATION \"PLACE_SHIP %d %d %c %d %s\": %s\n", y, x, direction, whichShip, shipType, NOT_IN_STARTING_POSITION);
				exit(0);
			}
			return true;
		case W:
			if (x + (shipLength - 1) > player->x2) {
				printf_s("INVALID OPERATION \"PLACE_SHIP %d %d %c %d %s\": %s\n", y, x, direction, whichShip, shipType, NOT_IN_STARTING_POSITION);
				exit(0);
			}
			return true;
		case E:
			if (x - (shipLength - 1) < player->x1) {
				printf_s("INVALID OPERATION \"PLACE_SHIP %d %d %c %d %s\": %s\n", y, x, direction, whichShip, shipType, NOT_IN_STARTING_POSITION);
				exit(0);
			}
			return true;
		}
	}
	printf_s("INVALID OPERATION \"PLACE_SHIP %d %d %c %d %s\": %s\n", y, x, direction, whichShip, shipType, NOT_IN_STARTING_POSITION);
	exit(0);
}

void setShipSegments(char**& board, char shipSegments[MAX_SHIP_SEGMENTS], int y, int x, char direction, int i, int j) {
	switch (direction) {
	case N: case S:
		if (shipSegments[i] == '1') {
			board[j][x] = '+';
		}
		else {
			board[j][x] = 'x';
		}
		break;
	case W: case E:
		if (shipSegments[i] == '1') {
			board[y][j] = '+';
		}
		else {
			board[y][j] = 'x';
		}
		break;
	}
}

void dockShip(char**& board, int y, int x, char direction, int shipLenght, char shipSegments[MAX_SHIP_SEGMENTS]) {
	int i = 0;
	if (shipSegments[i] == '1') {
		board[y][x] = '+';

	}
	else if (shipSegments[i] == '0') {
		board[y][x] = 'x';
	}
	i = shipLenght - 1;
	switch (direction) {
	case S:
		for (int j = y - (shipLenght - 1); j < y; j++) {
			setShipSegments(board, shipSegments, y, x, direction, i, j);
			i--;
		}
		break;
	case N:
		for (int j = y + shipLenght - 1; j > y; j--) {
			setShipSegments(board, shipSegments, y, x, direction, i, j);
			i--;
		}
		break;
	case W:
		for (int j = x + shipLenght - 1; j > x; j--) {
			setShipSegments(board, shipSegments, y, x, direction, i, j);
			i--;
		}
		break;
	case E:
		for (int j = x - (shipLenght - 1); j < x; j++) {
			setShipSegments(board, shipSegments, y, x, direction, i, j);
			i--;
		}
		break;
	}
}

bool isShipDefined(PLAYER* player, int y, int x, char direction, char shipType[SHIP_TYPE_LENGTH], int shipTypeArrayId, int whichShip) {
	if (player->ships[shipTypeArrayId][whichShip].isDefined) {
		return true;
	}
	printf_s("INVALID OPERATION \"PLACE_SHIP %d %d %c %d %s\": %s\n", y, x, direction, whichShip, shipType, ALL_SHIPS_OF_THE_CLASS_ALREADY_SET);
	exit(0);
}

bool isShipSetOnBoard(PLAYER* player, int y, int x, char direction, char shipType[SHIP_TYPE_LENGTH], int shipTypeArrayId, int whichShip) {
	if (!(player->ships[shipTypeArrayId][whichShip].isSetOnBoard)) {
		return true;
	}
	printf_s("INVALID OPERATION \"PLACE_SHIP %d %d %c %d %s\": %s\n", y, x, direction, whichShip, shipType, SHIP_ALREADY_PRESENT);
	exit(0);
}

void setSectionsOfShip(PLAYER* player, int shipTypeArrayId, int whichShip, int shipLength, char shipSegments[MAX_SHIP_SEGMENTS]) {
	for (int i = 0; i <= (shipLength - 1); i++) {
		if (i == 0) {
			if (shipSegments[i] == '0') {
				player->ships[shipTypeArrayId][whichShip].functionality[CAN_SEE] = false;
			}
			else {
				player->ships[shipTypeArrayId][whichShip].specialSegments[i] = '@';
			}
		}
		if (i == 1) {
			if (shipSegments[i] == '0') {
				player->ships[shipTypeArrayId][whichShip].functionality[CAN_SHOOT] = false;
			}
			else {
				player->ships[shipTypeArrayId][whichShip].specialSegments[i] = '!';
			}
		}
		if (i == (shipLength - 1)) {
			if (shipSegments[i] == '0') {
				player->ships[shipTypeArrayId][whichShip].functionality[CAN_MOVE] = false;
			}
			else {
				player->ships[shipTypeArrayId][whichShip].specialSegments[i] = '%';
			}
		}
	}
}

bool areAllShipsPlaced(PLAYER* player) {
	for (int i = 0; i < SHIP_TYPES; i++) {
		for (int j = 0; j < MAX_SHIPS_Q; j++) {
			if (player->ships[i][j].isDefined == true && player->ships[i][j].isSetOnBoard == false) {
				return false;
			}
		}
	}
	return true;
}

void makeShot(PLAYER* player, int y, int x) {
	for (int i = 0; i < SHIP_TYPES; i++) {
		for (int j = 0; j < MAX_SHIPS_Q; j++) {
			if (player->ships[i][j].isDefined) {
				char direction = player->ships[i][j].direction;
				int yHead = player->ships[i][j].yHead;
				int xHead = player->ships[i][j].xHead;
				int shipLength = player->ships[i][j].shipLength;
				int l = 0;
				switch (direction) {
				case N:
					for (int k = yHead; k <= yHead + shipLength; k++) {
						if (k == y && xHead == x) {
							if (player->ships[i][j].specialSegments[l] == '!') {
								player->ships[i][j].functionality[CAN_SHOOT] = false;
							}
							if (player->ships[i][j].specialSegments[l] == '%') {
								player->ships[i][j].functionality[CAN_MOVE] = false;
							}
							player->ships[i][j].segments[l] = '0';
							player->parts_remaining--;
						}
						l++;
					}
					break;
				case S:
					for (int k = yHead; k >= yHead - shipLength; k--) {
						if (k == y && xHead == x) {
							if (player->ships[i][j].specialSegments[l] == '!') {
								player->ships[i][j].functionality[CAN_SHOOT] = false;
							}
							if (player->ships[i][j].specialSegments[l] == '%') {
								player->ships[i][j].functionality[CAN_MOVE] = false;
							}
							player->ships[i][j].segments[l] = '0';
							player->parts_remaining--;
						}
						l++;
					}
					break;
				case E:
					for (int k = xHead; k >= xHead - shipLength; k--) {
						if (k == x && yHead == y) {

							if (player->ships[i][j].specialSegments[l] == '!') {
								player->ships[i][j].functionality[CAN_SHOOT] = false;
							}
							if (player->ships[i][j].specialSegments[l] == '%') {
								player->ships[i][j].functionality[CAN_MOVE] = false;
							}
							player->ships[i][j].segments[l] = '0';
							player->parts_remaining--;
						}
						l++;
					}
					break;
				case W:
					for (int k = xHead; k <= xHead + shipLength; k++) {
						if (k == x && yHead == y) {
							if (player->ships[i][j].specialSegments[l] == '!') {
								player->ships[i][j].functionality[CAN_SHOOT] = false;
							}
							if (player->ships[i][j].specialSegments[l] == '%') {
								player->ships[i][j].functionality[CAN_MOVE] = false;
							}
							player->ships[i][j].segments[l] = '0';
							player->parts_remaining--;
						}
						l++;
					}
					break;
				}
			}

		}
	}
}

void shoot(char**& board, int* yBoard, int* xBoard, PLAYER* activePlayer, PLAYER* secondPlayer) {
	int y, x;
	bool areActivePlayerShipsPlaced = areAllShipsPlaced(activePlayer);
	bool areSecondPlayerShipsPlaced = areAllShipsPlaced(secondPlayer);
	cin >> y;
	cin >> x;
	if (y < *yBoard && x < *xBoard) {
		if (areActivePlayerShipsPlaced && areSecondPlayerShipsPlaced) {
			if (board[y][x] == '+') {
				makeShot(secondPlayer, y, x);
				board[y][x] = 'x';
				if (secondPlayer->parts_remaining == 0) {
					char playerWhoWon = checkWhichPlayer(activePlayer);
					printf_s("%c won", playerWhoWon);
					for (int i = 0; i < *yBoard; i++) {
						free(board[i]);
					}
					free(board);
					exit(0);
				}
			}
		}
		else {
			printf_s("INVALID OPERATION \"SHOOT %d %d\": %s\n", y, x, NOT_ALL_SHIPS_PLACED);
			exit(0);
		}
	}
	else {
		printf_s("INVALID OPERATION \"SHOOT %d %d\": %s\n", y, x, FIELD_DOES_NOT_EXIST);
		exit(0);
	}
}

int* getCannonPosition(PLAYER* player, int shipTypeArrayId, int whichShip) {
	char direction = player->ships[shipTypeArrayId][whichShip].direction;
	int y = player->ships[shipTypeArrayId][whichShip].yHead;
	int x = player->ships[shipTypeArrayId][whichShip].xHead;
	int* position = (int*)malloc(sizeof(int) * 2);
	switch (direction) {
	case N:
		position[0] = y + 1;
		position[1] = x;
		break;
	case S:
		position[0] = y - 1;
		position[1] = x;
		break;
	case E:
		position[0] = y;
		position[1] = x - 1;
		break;
	case W:
		position[0] = y;
		position[1] = x + 1;
		break;
	default:
		break;
	}
	return position;
}

void shoot_extended(char**& board, int* yBoard, int* xBoard, PLAYER* activePlayer, PLAYER* secondPlayer) {
	int whichShip, y, x, shipTypeArrayId, shipLength;
	char shipType[SHIP_TYPE_LENGTH];
	cin >> whichShip; cin >> shipType; cin >> y; cin >> x;
	shipTypeArrayId = getShipTypeArrayId(shipType);
	bool areActivePlayerShipsPlaced = areAllShipsPlaced(activePlayer);
	bool areSecondPlayerShipsPlaced = areAllShipsPlaced(secondPlayer);
	if (y < *yBoard && x < *xBoard) {
		if (areActivePlayerShipsPlaced && areSecondPlayerShipsPlaced) {
			if (activePlayer->ships[shipTypeArrayId][whichShip].functionality[CAN_SHOOT]) {
				if (activePlayer->ships[shipTypeArrayId][whichShip].possibleShots > 0) {
					int* postion = getCannonPosition(activePlayer, shipTypeArrayId, whichShip);
					int shotRange = sqrt(pow(abs(postion[0] - y), 2) + pow(abs(postion[1] - x), 2));
					shipLength = measureShip(shipType);
					if (shotRange <= (double)shipLength) {
						board[y][x] = 'x';
						makeShot(secondPlayer, y, x);
						if (secondPlayer->parts_remaining == 0) {
							char playerWhoWon = checkWhichPlayer(activePlayer);
							printf_s("%c won", playerWhoWon);
							for (int i = 0; i < *yBoard; i++) {
								free(board[i]);
							}
							free(board);
							exit(0);
						}
						activePlayer->ships[shipTypeArrayId][whichShip].possibleShots--;
					}
					else {
						printf_s("INVALID OPERATION \"SHOOT %d %s %d %d\": %s\n", whichShip, shipType, y, x, SHOOTING_TOO_FAR);
						exit(0);
					}
					free(postion);
				}
				else {
					printf_s("INVALID OPERATION \"SHOOT %d %s %d %d\": %s\n", whichShip, shipType, y, x, TOO_MANY_SHOOTS);
					exit(0);
				}
			}
			else {
				printf_s("INVALID OPERATION \"SHOOT %d %s %d %d\": %s\n", whichShip, shipType, y, x, SHIP_CANNOT_SHOOT);
				exit(0);
			}
		}
		else {
			printf_s("INVALID OPERATION \"SHOOT %d %s %d %d\": %s\n", whichShip, shipType, y, x, NOT_ALL_SHIPS_PLACED);
			exit(0);
		}
	}
	else {
		printf_s("INVALID OPERATION \"SHOOT %d %s %d %d\": %s\n", whichShip, shipType, y, x, FIELD_DOES_NOT_EXIST);
		exit(0);
	}
}

void reef(char**& board, int* yBoard, int* xBoard) {
	int y, x;
	cin >> y;
	cin >> x;
	if (y < *yBoard && y >= 0 && x < *xBoard && x >= 0) {
		board[y][x] = '#';
	}
	else {
		printf_s("INVALID OPERATION \"REEF\": %s\n", REEF_IS_NOT_PLACED_ON_BOARD);
		exit(0);
	}
}

void board_size(char**& board, int* ySize, int* xSize) {
	int y, x;
	cin >> y;
	cin >> x;
	for (int i = 0; i < BOARD_Y; i++) {
		free(board[i]);
	}
	free(board);

	board = (char**)malloc(y * x * sizeof(char));
	for (int i = 0; i < y; i++) {
		board[i] = (char*)malloc(x * sizeof(char));
	}

	for (int i = 0; i < y; i++) {
		for (int j = 0; j < x; j++) {
			board[i][j] = ' ';
		}
	}
	*ySize = y;
	*xSize = x;
}

bool isTooClose(char** board, int* yBoard, int* xBoard, int y, int x, int direction, int shipLength) {
	int horizontalOrVertical = 0;
	if (direction == N || direction == W) {
		horizontalOrVertical = 1;
	}
	else {
		horizontalOrVertical = -1;
	}
	int additionalBorders = 2;
	if (board[y][x] == '+' || board[y][x] == 'x') {
		return true;
	}
	if (direction == N || direction == S) {
		for (int i = -1; i < shipLength + 1; i++) {
			for (int j = -1; j < additionalBorders; j++) {
				if (x + j < 0 || x + j > *xBoard - 1 || y + (i * horizontalOrVertical) > *yBoard - 1 || y + (i * horizontalOrVertical) < 0) {
					continue;
				}
				else {
					if (board[y + (i * horizontalOrVertical)][x + j] == '+' || board[y + (i * horizontalOrVertical)][x + j] == 'x') {
						return true;
					}
				}
			}
		}
		return false;
	}
	else {
		for (int i = -1; i < additionalBorders; i++) {
			for (int j = -1; j < shipLength + 1; j++) {
				if (x + (j * horizontalOrVertical) < 0 || x + (j * horizontalOrVertical) > *xBoard - 1 || y + i > *yBoard - 1 || y + i < 0) {
					continue;
				}
				else {
					if (board[y + i][x + (j * horizontalOrVertical)] == '+' || board[y + i][x + (j * horizontalOrVertical)] == 'x') {
						return true;
					}
				}
			}
		}
		return false;
	}
}

void place_ship(char** board, int* yBoard, int* xBoard, PLAYER* player) {
	int y, x, whichShip;
	char direction, shipType[SHIP_TYPE_LENGTH], shipSegments[MAX_SHIP_SEGMENTS] = "";
	cin >> y; cin >> x; cin >> direction; cin >> whichShip; cin >> shipType;
	int shipLength = measureShip(shipType); 
	for (int i = 0; i < shipLength; i++) {
		shipSegments[i] = '1';
	}
	if (isPlaceInInitialPosition(player, y, x, direction, whichShip, shipType, shipLength)) {
		if (!isTooClose(board, yBoard, xBoard, y, x, direction, shipLength)) {
			if (isReef(board, y, x, direction, whichShip, shipType, shipLength)) {
				int shipTypeArrayId = getShipTypeArrayId(shipType);
				if (isShipDefined(player, y, x, direction, shipType, shipTypeArrayId, whichShip)) {
					if (isShipSetOnBoard(player, y, x, direction, shipType, shipTypeArrayId, whichShip)) {
						dockShip(board, y, x, direction, shipLength, shipSegments);
						char shipSegments[MAX_SHIP_SEGMENTS] = "";
						for (int i = 0; i < shipLength; i++) {
							shipSegments[i] = '1';
						}
						setSectionsOfShip(player, shipTypeArrayId, whichShip, shipLength, shipSegments);
						player->ships[shipTypeArrayId][whichShip].direction = direction;
						player->ships[shipTypeArrayId][whichShip].isSetOnBoard = true;
						player->ships[shipTypeArrayId][whichShip].yHead = y;
						player->ships[shipTypeArrayId][whichShip].xHead = x;
						strcpy_s(player->ships[shipTypeArrayId][whichShip].segments, shipSegments);
						player->parts_remaining += shipLength;
					}
				}
			}
		}
		else {
			printf_s("INVALID OPERATION \"PLACE_SHIP %d %d %c %d %s\": %s\n", y, x, direction, whichShip, shipType, PLACING_SHIP_TOO_CLOSE_TO_OTHER_SHIP);
			exit(0);
		}
	}
}

void ship(char**& board, int* yBoard, int* xBoard, PLAYER* player) {
	int y, x, whichShip;
	char direction, shipType[SHIP_TYPE_LENGTH], shipSegments[MAX_SHIP_SEGMENTS], playerName;
	playerName = checkWhichPlayer(player);
	cin >> y; cin >> x; cin >> direction; cin >> whichShip; cin >> shipType; cin >> shipSegments;
	int shipLength = measureShip(shipType);
	if (!isTooClose(board, yBoard, xBoard, y, x, direction, shipLength)) {
		if (isReef(board, y, x, direction, whichShip, shipType, shipLength)) {
			int shipTypeArrayId = getShipTypeArrayId(shipType);
			if (isShipDefined(player, y, x, direction, shipType, shipTypeArrayId, whichShip)) {
				if (isShipSetOnBoard(player, y, x, direction, shipType, shipTypeArrayId, whichShip)) {
					dockShip(board, y, x, direction, shipLength, shipSegments);
					player->ships[shipTypeArrayId][whichShip].direction = direction;
					player->ships[shipTypeArrayId][whichShip].isSetOnBoard = true;
					player->ships[shipTypeArrayId][whichShip].yHead = y;
					player->ships[shipTypeArrayId][whichShip].xHead = x;
					strcpy_s(player->ships[shipTypeArrayId][whichShip].segments, shipSegments);
					setSectionsOfShip(player, shipTypeArrayId, whichShip, shipLength, shipSegments);
					for (int i = 0; i < sizeof(shipSegments) / sizeof(shipSegments[0]); i++) {
						if (shipSegments[i] == '1') {
							player->parts_remaining++;
						}
					}
				}
			}
		}
	}
	else {
		printf_s("INVALID OPERATION \"SHIP %c %d %d %c %d %s %s\": %s\n", playerName, y, x, direction, whichShip, shipType, shipSegments, PLACING_SHIP_TOO_CLOSE_TO_OTHER_SHIP);
		exit(0);
	}
}

void checkIsOutOfBoardF(int* yBoard, int* xBoard, PLAYER* player, int whichShip, char shipType[SHIP_TYPE_LENGTH], char moveDirection) {
	int shipTypeArrayId = getShipTypeArrayId(shipType);
	int y = player->ships[shipTypeArrayId][whichShip].yHead;
	int x = player->ships[shipTypeArrayId][whichShip].xHead;
	char direction = player->ships[shipTypeArrayId][whichShip].direction;
	int tmp = 0;
	int yBoardBorder = *yBoard - 1;
	int xBoardBorder = *xBoard - 1;
	if (direction == N || direction == W) {
		tmp = -1;
	}
	else {
		tmp = 1;
	}
	switch (direction) {
	case N: case S:
		y = y + tmp;
		if (y<0 || y > yBoardBorder) {
			printf_s("INVALID OPERATION \"MOVE %d %s %c\": %s\n", whichShip, shipType, moveDirection, SHIP_WENT_FROM_BOARD);
			exit(0);
		}
		break;
	case W: case E:
		x = x + tmp;
		if (x<0 || x > xBoardBorder) {
			printf_s("INVALID OPERATION \"MOVE %d %s %c\": %s\n", whichShip, shipType, moveDirection, SHIP_WENT_FROM_BOARD);
			exit(0);
		}
		break;
	default:
		break;
	}
}

void checkIsOutOfBoardRorL(int* yBoard, int* xBoard, PLAYER* player, int whichShip, char shipType[SHIP_TYPE_LENGTH], char moveDirection, char RorL) {
	int shipLength = measureShip(shipType);
	int shipTypeArrayId = getShipTypeArrayId(shipType);
	int y = player->ships[shipTypeArrayId][whichShip].yHead;
	int x = player->ships[shipTypeArrayId][whichShip].xHead;
	char direction = player->ships[shipTypeArrayId][whichShip].direction;
	int horizontalOrVertical = 0;
	int yBoardBorder = *yBoard - 1;
	int xBoardBorder = *xBoard - 1;
	if (RorL == R) {
		if (direction == N || direction == W) {
			horizontalOrVertical = 1;
		}
		else {
			horizontalOrVertical - 1;
		}
	}
	else {
		if (direction == N || direction == W) {
			horizontalOrVertical = -1;
		}
		else {
			horizontalOrVertical = 1;
		}
	}
	switch (direction) {
	case N: case S:
		x = x + horizontalOrVertical * (shipLength - 1);
		y = y - horizontalOrVertical;
		if (y<0 || y > yBoardBorder || x < 0 || x > xBoardBorder) {
			printf_s("INVALID OPERATION \"MOVE %d %s %c\": %s\n", whichShip, shipType, moveDirection, SHIP_WENT_FROM_BOARD);
			exit(0);
		}
		break;
	case W: case E:
		x = x + horizontalOrVertical;
		y = y - horizontalOrVertical * (shipLength - 1);
		if (y<0 || y > yBoardBorder || x < 0 || x> xBoardBorder) {
			printf_s("INVALID OPERATION \"MOVE %d %s %c\": %s\n", whichShip, shipType, moveDirection, SHIP_WENT_FROM_BOARD);
			exit(0);
		}
		break;
	default:
		break;
	}
}

bool isOutOfBoard(int* yBoard, int* xBoard, PLAYER* player, int whichShip, char shipType[SHIP_TYPE_LENGTH], char moveDirection) {
	switch (moveDirection) {
	case F:
		checkIsOutOfBoardF(yBoard, xBoard, player, whichShip, shipType, moveDirection);
		break;
	case R:
		checkIsOutOfBoardRorL(yBoard, xBoard, player, whichShip, shipType, moveDirection, R);
		break;
	case L:
		checkIsOutOfBoardRorL(yBoard, xBoard, player, whichShip, shipType, moveDirection, L);
		break;
	default:
		break;
	}
	return true;
}

char* hideShipTemporary(char**& board, int y, int x, char direction, int shipLength) {
	char* shipSegments = (char*)malloc(sizeof(char) * MAX_SHIP_SEGMENTS);
	int j = 0;
	switch (direction) {
	case N:
		for (int i = y; i <= y + (shipLength - 1); i++) {
			shipSegments[j] = board[i][x];
			board[i][x] = ' ';
			j++;
		}
		break;
	case S:
		for (int i = y; i >= y - (shipLength - 1); i--) {
			shipSegments[j] = board[i][x];
			board[i][x] = ' ';
			j++;
		}
		break;
	case E:
		for (int i = x; i >= x - (shipLength - 1); i--) {
			shipSegments[j] = board[y][i];
			board[y][i] = ' ';
			j++;
		}
		break;

	case W:
		for (int i = x; i <= x + (shipLength - 1); i++) {
			shipSegments[j] = board[y][i];
			board[y][i] = ' ';
			j++;
		}
		break;
	default:
		break;
	}
	return shipSegments;
}

void showShipTemporary(char**& board, int y, int x, char direction, int shipLength, char* shipSegments) {
	int j = 0;
	switch (direction) {
	case N:
		for (int i = y; i <= y + (shipLength - 1); i++) {
			board[i][x] = shipSegments[j];
			j++;
		}
		break;
	case S:
		for (int i = y; i >= y - (shipLength - 1); i--) {
			board[i][x] = shipSegments[j];
			j++;
		}
		break;
	case E:
		for (int i = x; i >= x - (shipLength - 1); i--) {
			board[y][i] = shipSegments[j];
			j++;
		}
		break;
	case W:
		for (int i = x; i <= x + (shipLength - 1); i++) {
			board[y][i] = shipSegments[j];
			j++;
		}
		break;
	default:
		break;
	}
	free(shipSegments);
}

bool checkIsTooCloseF(char**& board, int* yBoard, int* xBoard, PLAYER* player, int shipTypeArrayId, int whichShip, int shipLength ) {
	int y = player->ships[shipTypeArrayId][whichShip].yHead;
	int x = player->ships[shipTypeArrayId][whichShip].xHead;
	int direction = player->ships[shipTypeArrayId][whichShip].direction;
	char* hiddenShipSegments = hideShipTemporary(board, y, x, direction, shipLength);
	switch (direction) {
	case N:
		if (isTooClose(board, yBoard, xBoard, y - 1, x, direction, shipLength)) {
			return true;
		}
		break;
	case S:
		if (isTooClose(board, yBoard, xBoard, y + 1, x, direction, shipLength)) {
			return true;
		}
		break;
	case E:
		if (isTooClose(board, yBoard, xBoard, y, x + 1, direction, shipLength)) {
			return true;
		}
		break;
	case W:
		if (isTooClose(board, yBoard, xBoard, y, x - 1, direction, shipLength)) {
			return true;
		}
		break;
	default:
		break;
	}
	showShipTemporary(board, y, x, direction, shipLength, hiddenShipSegments);
	return false;
}

void changeDirection(PLAYER* player, int shipTypeArrayId, int whichShip, char RorL, char direction) {
	switch (RorL) {
	case R:
		switch (direction) {
		case N:
			player->ships[shipTypeArrayId][whichShip].direction = E;
			break;
		case S:
			player->ships[shipTypeArrayId][whichShip].direction = W;
			break;
		case E:
			player->ships[shipTypeArrayId][whichShip].direction = S;
			break;
		case W:
			player->ships[shipTypeArrayId][whichShip].direction = N;
			break;
		}
		break;
	case L:
		switch (direction) {
		case N:
			player->ships[shipTypeArrayId][whichShip].direction = W;
			break;
		case S:
			player->ships[shipTypeArrayId][whichShip].direction = E;
			break;
		case E:
			player->ships[shipTypeArrayId][whichShip].direction = N;
			break;
		case W:
			player->ships[shipTypeArrayId][whichShip].direction = S;
			break;
		}
		break;
	}
}

bool checkIsTooCloseRorL(char**& board, int* yBoard, int* xBoard, PLAYER* player, int shipTypeArrayId, int whichShip, int shipLength, char RorL) {
	int y = player->ships[shipTypeArrayId][whichShip].yHead;
	int x = player->ships[shipTypeArrayId][whichShip].xHead;
	char direction = player->ships[shipTypeArrayId][whichShip].direction;
	int horizontalOrVertical = 0;
	if (RorL == R) {
		if (direction == N || direction == W) {
			horizontalOrVertical = -1;
		}
		else if (direction == S || direction == E) {
			horizontalOrVertical = 1;
		}
	}
	else {
		if (direction == N || direction == W) {
			horizontalOrVertical = 1;
		}
		else if (direction == S || direction == E) {
			horizontalOrVertical = -1;
		}
	}
	int newY = 0;
	int newX = 0;
	if (direction == 'N' || direction == 'S') {
		newY = y + horizontalOrVertical;
		newX = x - horizontalOrVertical * (shipLength - 1);
	}
	else {
		newY = y + horizontalOrVertical * (shipLength - 1);
		newX = x - horizontalOrVertical;
	}
	char* hiddenShipSegments = hideShipTemporary(board, y, x, direction, shipLength);
	char tmpDirection = direction;
	changeDirection(player, shipTypeArrayId, whichShip, RorL, direction);
	char newDirection = player->ships[shipTypeArrayId][whichShip].direction;
	if (isTooClose(board, yBoard, xBoard, newY, newX, newDirection, shipLength)) {
		return true;
	}
	else {
		player->ships[shipTypeArrayId][whichShip].direction = tmpDirection;
		showShipTemporary(board, y, x, direction, shipLength, hiddenShipSegments);
		return false;
	}
}

bool isMovedTooClose(char** board, int* yBoard, int* xBoard, PLAYER* player, int whichShip, char shipType[SHIP_TYPE_LENGTH], char moveDirection) {
	int shipLength = measureShip(shipType);
	int shipTypeArrayId = getShipTypeArrayId(shipType);
	switch (moveDirection) {
	case F:
		if (checkIsTooCloseF(board, yBoard, xBoard, player, shipTypeArrayId, whichShip,  shipLength)) {
			return false;
		}
		break;
	case R:
		if (checkIsTooCloseRorL(board, yBoard, xBoard, player, shipTypeArrayId, whichShip, shipLength, R)) {
			return false;
		}
		break;
	case L:
		if (checkIsTooCloseRorL(board, yBoard, xBoard, player, shipTypeArrayId, whichShip, shipLength, L)) {
			return false;
		}
		break;
	default:
		break;
	}
	return true;
}

void checkIsReefFandMoveShip(char**& board, PLAYER* player, int shipTypeArrayId, int whichShip, char shipType[SHIP_TYPE_LENGTH], int shipLength, char moveDirection) {
	int y = player->ships[shipTypeArrayId][whichShip].yHead;
	int x = player->ships[shipTypeArrayId][whichShip].xHead;
	char direction = player->ships[shipTypeArrayId][whichShip].direction;
	switch (direction) {
	case N:
		if (board[y - 1][x] == '#') {
			printf_s("INVALID OPERATION \"MOVE %d %s %c\": %s\n", whichShip, shipType, moveDirection, PLACING_SHIP_ON_REEF);
			exit(0);
		}
		board[y + (shipLength - 1)][x] = ' ';
		board[y - 1][x] = '+';
		player->ships[shipTypeArrayId][whichShip].yHead -= 1;
		break;
	case S:
		if (board[y + 1][x] == '#') {
			printf_s("INVALID OPERATION \"MOVE %d %s %c\": %s\n", whichShip, shipType, moveDirection, PLACING_SHIP_ON_REEF);
			exit(0);
		}
		board[y - (shipLength - 1)][x] = ' ';
		board[y + 1][x] = '+';
		player->ships[shipTypeArrayId][whichShip].yHead += 1;
		break;
	case W:
		if (board[y][x - 1] == '#') {
			printf_s("INVALID OPERATION \"MOVE %d %s %c\": %s\n", whichShip, shipType, moveDirection, PLACING_SHIP_ON_REEF);
			exit(0);
		}
		board[y][x + (shipLength - 1)] = ' ';
		board[y][x - 1] = '+';
		player->ships[shipTypeArrayId][whichShip].xHead -= 1;
		break;
	case E:
		if (board[y][x + 1] == '#') {
			printf_s("INVALID OPERATION \"MOVE %d %s %c\": %s\n", whichShip, shipType, moveDirection, PLACING_SHIP_ON_REEF);
			exit(0);
		}
		board[y][x - (shipLength - 1)] = ' ';
		board[y][x + 1] = '+';
		player->ships[shipTypeArrayId][whichShip].xHead += 1;
		break;
	default:
		break;
	}
}

void moveShip(char**& board, int y, int x, int newY, int newX, char direction, char RorL) {
	int j = 0, tmp = 0, * tmpX = 0, * tmpY = 0, * tmpI = 0, i = 0;
	if (RorL == R) {
		tmp = 1;
		tmpX = &x;
		tmpY = &y;
		tmpI = &i;
	}
	else {
		tmp = -1;
		if (direction == W || direction == E) {
			tmpY = &i;
			tmpI = &y;
		}
		else {
			tmpX = &i;
			tmpI = &x;
		}
	}
	switch (direction) {
	case N:
		for (i = newX; *tmpI >= *tmpX; i -= tmp) {
			board[newY][i] = board[y + j][x];
			board[y + j][x] = ' ';
			j++;
		}
		break;
	case S:
		for (i = newX; *tmpI <= *tmpX; i += tmp) {
			board[newY][i] = board[y - j][x];
			board[y - j][x] = ' ';
			j++;
		}
		break;
	case E:
		for (i = newY; *tmpI >= *tmpY; i -= tmp) {
			board[i][newX] = board[y][x - j];
			board[y][x - j] = ' ';
			j++;
		}
		break;
	case W:
		for (i = newY; *tmpI <= *tmpY; i += tmp) {
			board[i][newX] = board[y][x + j];
			board[y][x + j] = ' ';
			j++;
		}
		break;
	}
}

void checkIsReefRorL(char** board, PLAYER* player, int shipTypeArrayId, int whichShip, char shipType[SHIP_TYPE_LENGTH], int shipLength, char moveDirection, char RorL) {
	int y = player->ships[shipTypeArrayId][whichShip].yHead;
	int x = player->ships[shipTypeArrayId][whichShip].xHead;
	char direction = player->ships[shipTypeArrayId][whichShip].direction;
	int tmp = 0, newY = 0, newX = 0, * tmpX = 0, * tmpY = 0, * tmpI = 0, i = 0;
	if (RorL == R) {
		tmp = 1;
		tmpX = &x;
		tmpY = &y;
		tmpI = &i;
	}
	else {
		tmp = -1;
		if (direction == W || direction == E) {
			tmpY = &i;
			tmpI = &y;
		}
		else {
			tmpX = &i;
			tmpI = &x;
		}
	}
	switch (direction) {
	case N:
		newY = y - 1;
		newX = x + tmp * (shipLength - 1);
		for (i = newX; *tmpI >= *tmpX; i -= tmp) {
			if (board[newY][i] == '#') {
				printf_s("INVALID OPERATION \"MOVE %d %s %c\": %s\n", whichShip, shipType, moveDirection, PLACING_SHIP_ON_REEF);
				exit(0);
			}
		}
		break;
	case S:
		newY = y + 1;
		newX = x - tmp * (shipLength - 1);
		for (i = newX; *tmpI <= *tmpX; i += tmp) {
			if (board[newY][i] == '#') {
				printf_s("INVALID OPERATION \"MOVE %d %s %c\": %s\n", whichShip, shipType, moveDirection, PLACING_SHIP_ON_REEF);
				exit(0);
			}
		}
		break;
	case W:
		newY = y - tmp * (shipLength - 1);
		newX = x - 1;
		for (i = newY; *tmpI <= *tmpY; i += tmp) {
			if (board[i][newX] == '#') {
				printf_s("INVALID OPERATION \"MOVE %d %s %c\": %s\n", whichShip, shipType, moveDirection, PLACING_SHIP_ON_REEF);
				exit(0);
			}
		}
		break;
	case E:
		newY = y + tmp * (shipLength - 1);
		newX = x + 1;
		for (i = newY; *tmpI <= *tmpY; i -= tmp) {
			if (board[i][newX] == '#') {
				printf_s("INVALID OPERATION \"MOVE %d %s %c\": %s\n", whichShip, shipType, moveDirection, PLACING_SHIP_ON_REEF);
				exit(0);
			}
		}
		break;
	default:
		break;
	}
	moveShip(board, y, x, newY, newX, direction, RorL);
	changeDirection(player, shipTypeArrayId, whichShip, RorL, direction);
	player->ships[shipTypeArrayId][whichShip].yHead = newY;
	player->ships[shipTypeArrayId][whichShip].xHead = newX;
}

void isReefAndDoMove(char** board, PLAYER* player, int whichShip, char shipType[SHIP_TYPE_LENGTH], char moveDirection) {
	int shipLength = measureShip(shipType);
	int shipTypeArrayId = getShipTypeArrayId(shipType);
	switch (moveDirection) {
	case F:
		checkIsReefFandMoveShip(board, player, shipTypeArrayId, whichShip, shipType, shipLength, moveDirection);
		break;
	case R:
		checkIsReefRorL(board, player, shipTypeArrayId, whichShip, shipType, shipLength, moveDirection, R);
		break;
	case L:
		checkIsReefRorL(board, player, shipTypeArrayId, whichShip, shipType, shipLength, moveDirection, L);
		break;
	default:
		break;
	}
}

void move(char** board, int* yBoard, int* xBoard, PLAYER* player) {
	int whichShip;
	char shipType[SHIP_TYPE_LENGTH], moveDirection;
	cin >> whichShip; cin >> shipType; cin >> moveDirection;
	int shipTypeArrayId = getShipTypeArrayId(shipType);
	if (player->ships[shipTypeArrayId][whichShip].functionality[CAN_MOVE]) {
		if (player->ships[shipTypeArrayId][whichShip].possibleMoves != 0) {
			if (isOutOfBoard(yBoard, xBoard, player, whichShip, shipType, moveDirection)) {
				if (isMovedTooClose(board, yBoard, xBoard, player, whichShip, shipType, moveDirection)) {
					isReefAndDoMove(board, player, whichShip, shipType, moveDirection);
					player->ships[shipTypeArrayId][whichShip].possibleMoves--;
				}
				else {
					printf_s("INVALID OPERATION \"MOVE %d %s %c\": %s\n", whichShip, shipType, moveDirection, PLACING_SHIP_TOO_CLOSE_TO_OTHER_SHIP);
					exit(0);
				}
			}
		}
		else {
			printf_s("INVALID OPERATION \"MOVE %d %s %c\": %s\n", whichShip, shipType, moveDirection, SHIP_MOVED_ALREADY);
			exit(0);
		}
	}
	else {
		printf_s("INVALID OPERATION \"MOVE %d %s %c\": %s\n", whichShip, shipType, moveDirection, SHIP_CANNOT_MOVE);
		exit(0);
	}

}

void next_player(gameOptions* game) {
	char name;
	cin >> name;
	game->nextPlayer = name;
}

void save_player(PLAYER* player) {
	char name = checkWhichPlayer(player);
	cout << "INIT_POSITION " << name << " " << player->y1 << " " << player->x1 << " " << player->y2 << " " << player->x2 << endl;
	cout << "SET_FLEET " << name << " ";
	int shipQ = 0;
	for (int i = 0; i < SHIP_TYPES; i++) {
		for (int j = 0; j < MAX_SHIPS_Q; j++) {
			if (player->ships[i][j].isDefined) {
				shipQ++;
			}
		}
		cout << shipQ << " ";
		shipQ = 0;
		i++;
		for (int j = 0; j < MAX_SHIPS_Q; j++) {
			if (player->ships[i][j].isDefined) {
				shipQ++;
			}
		}
		cout << shipQ << " ";
		shipQ = 0;
		i++;
		for (int j = 0; j < MAX_SHIPS_Q; j++) {
			if (player->ships[i][j].isDefined) {
				shipQ++;
			}
		}
		cout << shipQ << " ";
		shipQ = 0;
		i++;
		for (int j = 0; j < MAX_SHIPS_Q; j++) {
			if (player->ships[i][j].isDefined) {
				shipQ++;
			}
		}
		cout << shipQ << endl;
		i++;
	}
	for (int i = 0; i < SHIP_TYPES; i++) {
		for (int j = 0; j < MAX_SHIPS_Q; j++) {
			if (player->ships[i][j].isDefined) {
				cout << "SHIP " << name << " " << player->ships[i][j].yHead << " " << player->ships[i][j].xHead << " " << player->ships[i][j].direction << " " << j << " CAR " << player->ships[i][j].segments << endl;
			}
		}
		i++;
		for (int j = 0; j < MAX_SHIPS_Q; j++) {
			if (player->ships[i][j].isDefined) {
				cout << "SHIP " << name << " " << player->ships[i][j].yHead << " " << player->ships[i][j].xHead << " " << player->ships[i][j].direction << " " << j << " BAT " << player->ships[i][j].segments << endl;
			}
		}
		i++;
		for (int j = 0; j < MAX_SHIPS_Q; j++) {
			if (player->ships[i][j].isDefined) {
				cout << "SHIP " << name << " " << player->ships[i][j].yHead << " " << player->ships[i][j].xHead << " " << player->ships[i][j].direction << " " << j << " CRU " << player->ships[i][j].segments << endl;
			}
		}
		i++;
		for (int j = 0; j < MAX_SHIPS_Q; j++) {
			if (player->ships[i][j].isDefined) {
				cout << "SHIP " << name << " " << player->ships[i][j].yHead << " " << player->ships[i][j].xHead << " " << player->ships[i][j].direction << " " << j << " DES " << player->ships[i][j].segments << endl;
			}
		}
		i++;
	}
}

void save(gameOptions* game, char** board, PLAYER* player_A, PLAYER* player_B) {
	cout << "[state]" << endl;
	cout << "BOARD_SIZE " << game->boardY << " " << game->boardX << endl;
	cout << "NEXT_PLAYER " << game->nextPlayer << endl;
	save_player(player_A);
	save_player(player_B);
	cout << "[state]" << endl;
}

void manageState(gameOptions* game, char** board, int* yBoard, int* xBoard, PLAYER* player_A, PLAYER* player_B) {
	int whileCondition = 1;
	while (whileCondition) {
		int stateTask = 0;
		char stateOrder[INPUT_SIZE];
		char whichPlayer;
		cin >> stateOrder;
		stateTask = makeStateTask(stateOrder);
		switch (stateTask) {
		case STATE:
			whileCondition = 0;
			break;
		case PRINT:
			print(board, yBoard, xBoard, player_A, player_B);
			break;
		case SET_FLEET:
			whichPlayer = whichPlayerInState();
			if (whichPlayer == 'A') {
				set_fleet(player_A);
			}
			else if (whichPlayer == 'B') {
				set_fleet(player_B);
			}
			break;
		case NEXT_PLAYER:
			next_player(game);
			break;
		case REEF:
			reef(board, yBoard, xBoard);
			break;
		case BOARD_SIZE:
			board_size(board, yBoard, xBoard);
			break;
		case INIT_POSITION:
			whichPlayer = whichPlayerInState();
			if (whichPlayer == 'A') {
				init_position(player_A);
			}
			else if (whichPlayer == 'B') {
				init_position(player_B);
			}
			break;
		case SHIP:
			whichPlayer = whichPlayerInState();
			if (whichPlayer == 'A') {
				ship(board, yBoard, xBoard, player_A);
			}
			else if (whichPlayer == 'B') {
				ship(board, yBoard, xBoard, player_B);
			}
			break;
		case EXTENDED_SHIPS:
			game->extended = true;
			break;
		case SAVE:
			save(game, board, player_A, player_B);
			break;
		default:
			break;
		}
	}
}

void mangePlayer(gameOptions* game, char**& board, int* yBoard, int* xBoard, PLAYER* activePlayer, PLAYER* secondPlayer, char currentPlayer) {
	char playerName[PLAYER_NAME_SIZE];
	strcpy_s(playerName, activePlayer->name);
	int whileCondition = 1;
	while (whileCondition) {
		int playerTask = 0;
		char playerOrder[INPUT_SIZE];
		cin >> playerOrder;
		playerTask = makePlayerTask(playerOrder, playerName);
		char shootingPlayer = checkWhichPlayer(activePlayer);
		switch (playerTask) {
		case PLAYER_A:
			whileCondition = 0; //te dwa whileCondiotion = 0 sa po to zeby jak sie jest playerem A to po wpisaniu [playerB] nie dalo rady wyjsc
			break;
		case PLAYER_B:
			whileCondition = 0;
			break;
		case PLACE_SHIP:
			place_ship(board, yBoard, xBoard, activePlayer);
			break;
		case SHOOT:
			if (shootingPlayer == currentPlayer) {
				if (game->extended) {
					shoot_extended(board, yBoard, xBoard, activePlayer, secondPlayer);
				}
				else {
					shoot(board, yBoard, xBoard, activePlayer, secondPlayer);
				}
			}
			else {
				printf_s("INVALID OPERATION \"[player%c] \": %s\n", shootingPlayer, THE_OTHER_PLAYER_EXPECTED);
				exit(0);
			}
			break;
		case MOVE:
			move(board, yBoard, xBoard, activePlayer);
			break;
		default:
			break;
		}
	}
}

void initializeGame(char** board, PLAYER* player_A, PLAYER* player_B) {
	strncpy_s(player_A->name, "PLAYER_A", PLAYER_NAME_SIZE);
	strncpy_s(player_B->name, "PLAYER_B", PLAYER_NAME_SIZE);
	for (int i = 0; i < SHIP_TYPES - 1; i++) {
		for (int j = 0; j < DEFAULT_CAR_Q; j++) {
			player_A->ships[i][j].isDefined = true;
			player_A->ships[i][j].possibleMoves = 2;
			player_B->ships[i][j].isDefined = true;
			player_B->ships[i][j].possibleMoves = 2;
			player_A->ships[i][j].shipLength = 5;
			player_B->ships[i][j].shipLength = 5;
		}
		i++;
		for (int j = 0; j < DEFAULT_BAT_Q; j++) {
			player_A->ships[i][j].isDefined = true;
			player_B->ships[i][j].isDefined = true;
			player_A->ships[i][j].possibleShots = 4;
			player_B->ships[i][j].possibleShots = 4;
			player_A->ships[i][j].shipLength = 4;
			player_B->ships[i][j].shipLength = 4;
		}
		i++;
		for (int j = 0; j < DEFAULT_CRU_Q; j++) {
			player_A->ships[i][j].isDefined = true;
			player_B->ships[i][j].isDefined = true;
			player_A->ships[i][j].possibleShots = 3;
			player_B->ships[i][j].possibleShots = 3;
			player_A->ships[i][j].shipLength = 3;
			player_B->ships[i][j].shipLength = 3;
		}
		i++;
		for (int j = 0; j < DEFAULT_DES_Q; j++) {
			player_A->ships[i][j].isDefined = true;
			player_B->ships[i][j].isDefined = true;
			player_A->ships[i][j].possibleShots = 2;
			player_B->ships[i][j].possibleShots = 2;
			player_A->ships[i][j].shipLength = 2;
			player_B->ships[i][j].shipLength = 2;
		}
	}
	player_A->y1 = DEFAULT_Y1_A;
	player_A->y2 = DEFAULT_Y2_A;
	player_B->y1 = DEFAULT_Y1_B;
	player_B->y2 = DEFAULT_Y2_B;
	for (int i = 0; i < BOARD_Y; i++) {
		for (int j = 0; j < BOARD_X; j++) {
			board[i][j] = ' ';
		}
	}
}

void resetShips(PLAYER* player) {
	for (int i = 0; i < SHIP_TYPES; i++) {
		for (int j = 0; j < MAX_SHIPS_Q; j++) {
			if (i == 0) {
				player->ships[i][j].possibleMoves = 2;
			}
			else {
				if (i == 1) {
					player->ships[i][j].possibleShots = 4;
				}
				if (i == 2) {
					player->ships[i][j].possibleShots = 3;
				}
				if (i == 3) {
					player->ships[i][j].possibleShots = 2;
				}
				player->ships[i][j].possibleMoves = 3;
			}
		}
	}
}