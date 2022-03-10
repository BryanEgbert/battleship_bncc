#ifndef BATTLESHIP_H
#define BATTLESHIP_H

#define MAP_X 10
#define MAP_Y 10
#define MAX_BATTLESHIP 4
#define TOTAL_BATTLESHIP_LEN 14

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

void run();
void initMap(Player* player, const char* fileLocation);
void displayMap(Player* player, Map mapType);
void putBattleship();
void initPlayerInfo(Player* player);
void loadHomePage();
void startGame();
void playerTurn(int* turn, Player* player1, Player* player2);

#endif