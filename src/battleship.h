#ifndef BATTLESHIP_H
#define BATTLESHIP_H

#define MAP_X 10
#define MAP_Y 10
#define MAX_BATTLESHIP 4
#define TOTAL_BATTLESHIP_LEN 14

#include <stdbool.h>

typedef enum Map
{
	EMPTY = 0,
	BATTLESHIP = 1,
} Map;

#define BATTLESHIP_MAP BATTLESHIP
#define EMPTY_MAP EMPTY

typedef struct Player
{
	char name[50];
	char battleshipMap[11][11];
	char emptyMap[11][11];
	int ships[MAX_BATTLESHIP];
	int shipHitCount;
} Player;

typedef struct Coordinate
{
	int x, y;
} Coordinate;

typedef struct BattleshipPosition
{
	Coordinate coordinate;
	char pos;
} BattleshipPosition;

void initMap(Player* player, const char* fileLocation);
void initPlayerInfo(Player* player, const char* playerName);

void displayMap(Player* player, Map mapType);

void getCoordinateInput(Coordinate* coordinate);
void getBattleshipPosInput(Player* player, BattleshipPosition* battleshipPos);
bool putBattleshipIsAllowed(Player* player, BattleshipPosition* battleshipPos, int* index);


void hitCoordinate(int* turn, Player* player1, Player* player2, Coordinate* coordinate);
bool isGameOver(Player* player1, Player* player2);
void playerTurn(int* turn, Player* player1, Player* player2);

void enterPlayerNamePhase(Player* player1, Player* player2);
void putBattleshipPhase(Player* player1, Player* player2, BattleshipPosition* battleshipPos);
void attackPhase(Player* player1, Player* player2);

void loadHomePage();
void startGame();


#endif