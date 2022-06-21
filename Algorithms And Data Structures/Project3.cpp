#include <iostream>
#define MAX_INSTRUCTION_SIZE 33
#define GEN_ALL_POS_MOV "GEN_ALL_POS_MOV"
#define GEN_ALL_POS_MOV_CUT_IF_GAME_OVER "GEN_ALL_POS_MOV_CUT_IF_GAME_OVER"
#define SOLVE_GAME_STATE "SOLVE_GAME_STATE"
#define FIRST_PLAYER 1
#define SECOND_PLAYER 2
#define BOARD_IS_OVER -1
#define FIRST_PLAYER_WINS "FIRST_PLAYER_WINS"
#define SECOND_PLAYER_WINS "SECOND_PLAYER_WINS"
#define BOTH_PLAYERS_TIE "BOTH_PLAYERS_TIE"
#define FIRST_WIN 1
#define SECOND_WIN -1
#define TIE 0
#define MAX 1000
#define MIN -1000

using namespace std;

struct Board {
        int n;
        int m;
        int k;
        int activePlayer;
        int** fields;
        int fieldsNumber;
        Board(int n, int m, int k, int activePlayer, int** fields, int fieldsNumber):n(n), m(m),k(k), activePlayer(activePlayer), fields(fields), fieldsNumber(fieldsNumber) {
        }
};


Board *initializeBoard() {
        Board* board = nullptr;
        int n, m, k, activePlayer, fieldsNumber;
        cin >> n; cin >> m; cin >> k; cin >> activePlayer;
        int** fields = new int* [n];
        for (int i = 0; i < n; i++) {
                fields[i] = new int[m];
        }
        for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; j++) {
                        cin >> fields[i][j];
                }
        }
        fieldsNumber = n * m - 1;
        board = new Board(n, m, k, activePlayer, fields, fieldsNumber);
        return board;
}

bool checkRight(Board* board, int whichPlayer, int opponent) {
        int streak = 0;
        for (int i = 0; i < board->n; i++) {
                for (int j = 0; j < board->m; j++) {
                        if (j + board->k - 1 < board->m) {
                                if (!((board->fields[i][j] == 0) || board->fields[i][j] == opponent)) {
                                        for (int k = j; k <= j + board->k - 1; k++) {
                                                if (board->fields[i][k] == whichPlayer) {
                                                        streak++;
                                                        if (streak == board->k) {
                                                                return true;
                                                        }
                                                }
                                        }
                                        streak = 0;
                                }
                        }
                }
        }
        return false;
}
bool checkDown(Board* board, int whichPlayer, int opponent) {
        int streak = 0;
        for (int i = 0; i < board->n; i++) {
                for (int j = 0; j < board->m; j++) {
                        if (i + board->k - 1 < board->n) {
                                if (!((board->fields[i][j] == 0) || board->fields[i][j] == opponent)) {
                                        for (int k = i; k <= i + board->k - 1; k++) {
                                                if (board->fields[k][j] == whichPlayer) {
                                                        streak++;
                                                        if (streak == board->k) {
                                                                return true;
                                                        }
                                                }
                                        }
                                        streak = 0;
                                }
                        }
                }
        }
        return false;
}
bool checkDownRight(Board* board, int whichPlayer, int opponent) {
        int streak = 0;
        for (int i = 0; i < board->n; i++) {
                for (int j = 0; j < board->m; j++) {
                        if ((j + board->k - 1 < board->m) && (i + board->k - 1 < board->n)) {
                                if (!((board->fields[i][j] == 0) || board->fields[i][j] == opponent)) {
                                        int k, l;
                                        for (k = i, l = j; k <= i + board->k - 1; k++, l++) {
                                                if (board->fields[k][l] == whichPlayer) {
                                                        streak++;
                                                        if (streak == board->k) {
                                                                return true;
                                                        }
                                                }
                                        }
                                        streak = 0;
                                }
                        }
                }
        }
        return false;
}
bool checkDownLeft(Board* board, int whichPlayer, int opponent) {
        int streak = 0;
        for (int i = 0; i < board->n; i++) {
                for (int j = 0; j < board->m; j++) {
                        if ((j - (board->k - 1) >= 0) && (i + board->k - 1 < board->n)) {
                                if (!((board->fields[i][j] == 0) || board->fields[i][j] == opponent)) {
                                        int k, l;
                                        for (k = i, l = j; k <= i + board->k - 1; k++, l--) {
                                                if (board->fields[k][l] == whichPlayer) {
                                                        streak++;
                                                        if (streak == board->k) {
                                                                return true;
                                                        }
                                                }
                                        }
                                        streak = 0;
                                }
                        }
                }
        }
        return false;
}
int checkIfGameIsOver(Board* board, int whichPlayer, int opponent) {
        if (checkRight(board, whichPlayer, opponent) || checkDown(board, whichPlayer, opponent) || checkDownLeft(board, whichPlayer, opponent) || checkDownRight(board, whichPlayer, opponent)) {
                return true;
        }
        return false;
}
bool isBoardFull(Board* board) {
        for (int i = 0; i < board->n; i++) {
                for (int j = 0; j < board->m; j++) {
                        if (board->fields[i][j] == 0) {
                                return false;
                        }
                }
        }
        return true;
}
int printAllPositionPossibilities(Board* board, int lastFreeField) {
        int currentField = 0;
        bool lastFreeFieldChanged = false;
        for (int i = 0; i < board->n; i++) {
                for (int j = 0; j < board->m; j++) {
                        if (currentField >= lastFreeField) {
                                if (board->fields[i][j] == 0 && !lastFreeFieldChanged) {
                                        printf_s("%i ", board->activePlayer);
                                        lastFreeField = currentField+1;
                                        lastFreeFieldChanged = !lastFreeFieldChanged;
                                }
                                else {
                                        printf_s("%i ", board->fields[i][j]);
                                }
                        }
                        else {
                                printf_s("%i ", board->fields[i][j]);
                        }
                        currentField++;
                }
                printf_s("\n");
        }
        return lastFreeField;
}
int genAllMovesAndCheckIfGameOver(Board* board, Board* tmpBoard, int lastFreeField, int ** &fieldsIfGameNotOver, int currentBoardIteration) {
        // 2 zmienne do zapamietania z ktorego pola wstawiamy do tymczasowej tablicy -  bo jak nie jest skonczona plansza to trzeba wrocic do orginalnej
        int tmpI=0;
        int tmpJ=0;
        int currentField = 0;
        bool lastFreeFieldChanged = false;
        for (int i = 0; i < board->n; i++) {
                for (int j = 0; j < board->m; j++) {
                        if (currentField >= lastFreeField) {
                                if (board->fields[i][j] == 0 && !lastFreeFieldChanged) {
                                        fieldsIfGameNotOver[i + currentBoardIteration][j] = board->activePlayer;
                                        tmpBoard->fields[i][j] = board->activePlayer;
                                        tmpI = i;
                                        tmpJ = j;
                                        lastFreeField = currentField + 1;
                                        lastFreeFieldChanged = !lastFreeFieldChanged;
                                }
                                else {
                                        fieldsIfGameNotOver[i + currentBoardIteration][j] = board->fields[i][j];
                                }
                        }
                        else {
                                fieldsIfGameNotOver[i + currentBoardIteration][j] = board->fields[i][j];
                        }
                        currentField++;
                }
        }
        if ((checkIfGameIsOver(tmpBoard, FIRST_PLAYER, SECOND_PLAYER) || checkIfGameIsOver(tmpBoard, SECOND_PLAYER, FIRST_PLAYER))) {
                return BOARD_IS_OVER;
        }
        else {
                tmpBoard->fields[tmpI][tmpJ] = 0;
        }
        return lastFreeField;
}
int max(int a, int b) {
        if (a > b) {
                return a;
        }
        else {
                return b;
        }
}
int min(int a, int b) {
        if (a > b) {
                return b;
        }
        else {
                return a;
        }
}

int minimax(Board* board, int actualPlayer, int alpha, int beta){
        bool winnerFirst = checkIfGameIsOver(board, FIRST_PLAYER, SECOND_PLAYER);
        bool winnerSecond = checkIfGameIsOver(board, SECOND_PLAYER, FIRST_PLAYER);

        if (winnerFirst) {
                return FIRST_WIN;
        }
        if (winnerSecond) {
                return SECOND_WIN;
        }
        if (isBoardFull(board)) {
                return TIE;
        }
        if (actualPlayer == 1){
                int best = MIN;

                for (int i = 0; i < board->n; i++){
                        for (int j = 0; j < board->m; j++){
                                if (board->fields[i][j] == 0){
                                        board->fields[i][j] = 1;

                                        int eval = minimax(board, 2, alpha, beta);
                                        best = max(best, eval);
                                        alpha = max(alpha, best);
                                        board->fields[i][j] = 0;

                                        if (beta <= alpha) {
                                                break;
                                        }
                                }
                        }
                }
                return best;
        }
        else {
                int best = MAX;

                for (int i = 0; i < board->n; i++){
                        for (int j = 0; j < board->m; j++){
                                if (board->fields[i][j] == 0){
                                        board->fields[i][j] = 2;
                                        int eval =  minimax(board, 1, alpha, beta);
                                        best = min(best, eval);
                                        beta = min(beta, best);
                                        board->fields[i][j] = 0;
                                        if (beta <= alpha) {
                                                break;
                                        }
                                }
                        }
                }
                return best;
        }
}

int main() {
        char instruction[MAX_INSTRUCTION_SIZE];
        int lastFreeField = 0;
        int howManyPossibilities = 0;
        int winner;
        while (cin >> instruction) {
                if (!strcmp(GEN_ALL_POS_MOV, instruction)) {
                        Board *board = initializeBoard();
                        
                        for (int i = 0; i < board->n; i++) {
                                for (int j = 0; j < board->m; j++) {
                                        if (board->fields[i][j] == 0) {
                                                howManyPossibilities++;
                                        }
                                }
                        }
                        if ((checkIfGameIsOver(board, FIRST_PLAYER, SECOND_PLAYER) || checkIfGameIsOver(board, SECOND_PLAYER, FIRST_PLAYER))) {
                                howManyPossibilities = 0;
                                printf_s("%i \n", howManyPossibilities);
                        }
                        else {
                                printf_s("%i \n", howManyPossibilities);
                                for (int i = 0; i < howManyPossibilities; i++) {
                                        lastFreeField = printAllPositionPossibilities(board, lastFreeField);
                                }
                                howManyPossibilities = 0;

                        }
                        lastFreeField = 0;
                        
                }
                else if (!strcmp(GEN_ALL_POS_MOV_CUT_IF_GAME_OVER, instruction)) {
                        Board* board = initializeBoard();
                        Board* tmpBoard = new Board(board->n, board->m, board->k, board->activePlayer, board->fields, board->fieldsNumber);
                        
                        for (int i = 0; i < board->n; i++) {
                                for (int j = 0; j < board->m; j++) {
                                        if (board->fields[i][j] == 0) {
                                                howManyPossibilities++;
                                        }
                                }
                        }

                        // zarezwowanie pamieci do printowania wszystkich mozliwych ruchow jezli gra nie jest skonczona po ktoryms z ruchow
                        int** fieldsIfGameNotOver = new int* [board->n * howManyPossibilities];;

                        for (int i = 0; i < board->n * howManyPossibilities; i++) {
                                fieldsIfGameNotOver[i] = new int[board->m];
                        }

                        // jezeli n=2, m=2, a howManyPossibilities=4 to fieldsIfGameNotOver ma 16 miejsc na 4 plansze wiec trzeba skakac co 4 kolejne indexy za kazdym wywolaniem genAllMovesAndCheckIfGameOver
                        int howManyFieldsInSingleBoard = board->n;

                        //jezeli wprowadzona plansza jest skonczona to print 0 i koniec
                        if ((checkIfGameIsOver(board, FIRST_PLAYER, SECOND_PLAYER) || checkIfGameIsOver(board, SECOND_PLAYER, FIRST_PLAYER))) {
                                howManyPossibilities = 0;
                                printf_s("%i \n", howManyPossibilities);
                        }

                        else {
                                bool isGameOverAfterMove = false;
                                int currentBoardIteration = 0;
                                for (int k = 0; k < howManyPossibilities; k++) {
                                        lastFreeField = genAllMovesAndCheckIfGameOver(board, tmpBoard, lastFreeField, fieldsIfGameNotOver, currentBoardIteration);
                                        currentBoardIteration += howManyFieldsInSingleBoard;
                                        if (lastFreeField == BOARD_IS_OVER) {
                                                printf_s("1 \n");
                                                for (int i = 0; i < tmpBoard->n; i++) {
                                                        for (int j = 0; j < tmpBoard->m; j++) {
                                                                printf_s("%i ", tmpBoard->fields[i][j]);
                                                        }
                                                        printf_s("\n");
                                                }
                                                isGameOverAfterMove = true;
                                                break;
                                        }
                                }
                                if (!isGameOverAfterMove) {
                                        printf_s("%i \n", howManyPossibilities);
                                        for (int i = 0; i < board->n * howManyPossibilities; i++) {
                                                for (int j = 0; j < board->m ; ++j) {
                                                        printf_s("%i ", fieldsIfGameNotOver[i][j]);
                                                }
                                                printf_s("\n");
                                        }
                                }
                                howManyPossibilities = 0;

                        }
                        lastFreeField = 0;
                        for (int i = 0; i < board->n * howManyPossibilities; i++) {
                                delete [] fieldsIfGameNotOver[i];
                        }
                        delete[] fieldsIfGameNotOver;
                }
                else if (!strcmp(SOLVE_GAME_STATE, instruction)) {
                        Board *board = initializeBoard();
                        
                        winner = minimax(board, board->activePlayer, MIN, MAX);
                        if (winner == FIRST_WIN) {
                                printf_s(FIRST_PLAYER_WINS);
                                printf_s("\n");
                        }
                        else if (winner == SECOND_WIN) {
                                printf_s(SECOND_PLAYER_WINS);
                                printf_s("\n");
                        }
                        else {
                                printf_s(BOTH_PLAYERS_TIE);
                                printf_s("\n");
                        }
                }

        }
        return 0;
}