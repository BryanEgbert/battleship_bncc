#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "battleship.h"

void initMap(Player* player, const char* fileLocation)
{
	FILE *file = fopen(fileLocation, "r");

	if (file == NULL)
	{
		perror("Something's wrong when loading the map\n");
		exit(EXIT_FAILURE);
	}

	for (int i = 0; !feof(file); ++i)
		fscanf(file, "%[^\n]\n", player->battleshipMap[i]);

	fclose(file);

	for(int i = 0; i < MAP_Y; ++i)
		strcpy(player->emptyMap[i], player->battleshipMap[i]);
}

void displayMap(Player* player, Map mapType)
{
	if(mapType)
	{
		for(int i = 0; i < MAP_Y; ++i)
		{
			for(int j = 0; j < MAP_X; ++j)
				putchar(player->battleshipMap[i][j]);

			putchar('\n');
		}
	}
	else
	{
		for (int i = 0; i < MAP_Y; ++i)
		{
			for (int j = 0; j < MAP_X; ++j)
				putchar(player->emptyMap[i][j]);

			putchar('\n');
		}
	}

}

void initPlayerInfo(Player* player, const char* playerName)
{
	strcpy(player->name, playerName);

	player->shipHitCount = 0;

	player->ships[0] = 2;
	player->ships[1] = 3;
	player->ships[2] = 4;
	player->ships[3] = 5;
}

void getCoordinateInput(Coordinate* coordinate)
{
	printf("Choose Y coordinate (1 - %d): ", MAP_Y - 2);
	scanf("%d", &coordinate->y);

	while (coordinate->y < 1 || coordinate->y > MAP_Y - 2)
	{
		printf("Choose Y coordinate (1 - %d): ", MAP_Y - 2);
		scanf("%d", &coordinate->y);
	}

	printf("Choose X coordinate (1 - %d): ", MAP_X - 2);
	scanf("%d", &coordinate->x);
	getchar();

	while (coordinate->x < 1 || coordinate->x > MAP_X - 2)
	{
		printf("Choose X coordinate (1 - %d): ", MAP_X - 2);
		scanf("%d", &coordinate->x);
	}
}

void getBattleshipPosInput(Player* player, BattleshipPosition* battleshipPos)
{
	displayMap(player, BATTLESHIP_MAP);

	printf("Place vertical or horizontal (v/h): ");
	scanf("%c", &battleshipPos->pos);
	getchar();

	while (battleshipPos->pos != 'v' && battleshipPos->pos != 'h')
	{
		printf("False\nPlace vertical or horizontal (v/h): ");
		scanf("%c", &battleshipPos->pos);
		getchar();
	}

	getCoordinateInput(&battleshipPos->coordinate);
}

bool putBattleshipIsAllowed(Player* player, BattleshipPosition* battleshipPos, int* index)
{
	int x = battleshipPos->coordinate.x, y = battleshipPos->coordinate.y;
	bool isEmpty = true;

	if(battleshipPos->pos == 'h')
	{
		for(int j = x; j < player->ships[*index] + x; ++j)
			if(player->battleshipMap[y][j] == '@' || player->battleshipMap[y][j] == '#')
				isEmpty = false;

		if(!isEmpty)
		{
			printf("There's existing ship over there\n");
			getchar();

			return isEmpty;
		}

		for (int j = x; j < player->ships[*index] + x; ++j)
			player->battleshipMap[y][j] = '@';
	}
	else
	{
		for (int j = y; j < player->ships[*index] + y; ++j)
			if (player->battleshipMap[j][x] == '@' || player->battleshipMap[y][j] == '#')
				isEmpty = false;

		if(!isEmpty)
		{
			printf("There's existing ship over there\n");
			getchar();

			return isEmpty;
		}

		for(int j = y; j < player->ships[*index] + y; ++j)
			player->battleshipMap[j][x] = '@';
	}

	return isEmpty;
}

void hitCoordinate(int* turn, Player* player1, Player* player2, Coordinate* coordinate)
{
	int x = coordinate->x, y = coordinate->y;

	if(*turn % 2 != 0)
	{
		if (player1->emptyMap[y][x] == ' ')
		{
			if (player2->battleshipMap[y][x] == '@')
			{
				player1->emptyMap[y][x] = 'O';
				player1->shipHitCount++;

				printf("You hit a ship\n");
				getchar();
			}
			else
				player1->emptyMap[y][x] = 'X';
		}
	}
	else
	{
		if (player2->emptyMap[y][x] == ' ')
		{
			if (player1->battleshipMap[y][x] == '@')
			{
				player2->emptyMap[y][x] = 'O';
				player2->shipHitCount++;

				printf("You hit a ship\n");
				getchar();
			}
			else
				player2->emptyMap[y][x] = 'X';
		}
	} 
}

void playerTurn(int *turn, Player *player1, Player *player2)
{
	printf("\e[1;1H\e[2J");

	Coordinate coordinate;

	int x, y;

	if (*turn % 2 != 0)
	{
		displayMap(player1, EMPTY_MAP);

		printf("Player 1's turn\n");

		getCoordinateInput(&coordinate);
		hitCoordinate(turn, player1, player2, &coordinate);
	}
	else
	{
		displayMap(player2, EMPTY_MAP);

		printf("Player 2's turn\n");

		getCoordinateInput(&coordinate);
		hitCoordinate(turn, player1, player2, &coordinate);
	}
}

bool isGameOver(Player* player1, Player* player2)
{
	if (player1->shipHitCount == TOTAL_BATTLESHIP_LEN)
	{
		printf("%s wins\n", player1->name);
		return true;
	}
	else if (player2->shipHitCount == TOTAL_BATTLESHIP_LEN)
	{
		printf("%s wins", player2->name);
		return true;
	}

	return false;
}

void enterPlayerNamePhase(Player* player1, Player* player2)
{
	char name[50];

	printf("Enter player 1 name (max 50 chars.): ");
	scanf("%[^\n]", name);
	getchar();
	initPlayerInfo(player1, name);

	printf("\e[1;1H\e[2J");

	printf("Enter player 2 name (max 50 chars.): ");
	scanf("%[^\n]", name);
	getchar();
	initPlayerInfo(player2, name);
}

void putBattleshipPhase(Player *player1, Player *player2, BattleshipPosition *battleshipPos)
{
	printf("\e[1;1H\e[2J");
	printf("Put Your Battleships\n");

	int i = 0;

	printf("%s's turn\npress any key to continue.\n", player1->name);
	getchar();
	while (i < MAX_BATTLESHIP)
	{
		printf("\e[1;1H\e[2J");
		printf("Battleship lenght: %d\n", player1->ships[i]);

		getBattleshipPosInput(player1, battleshipPos);

		if (putBattleshipIsAllowed(player1, battleshipPos, &i))
			++i;
	}

	i = 0;

	printf("\e[1;1H\e[2J");
	printf("%s's turn\npress any key to continue.\n", player2->name);
	getchar();
	while (i < MAX_BATTLESHIP)
	{
		printf("\e[1;1H\e[2J");
		printf("Battleship lenght: %d\n", player2->ships[i]);

		getBattleshipPosInput(player2, battleshipPos);

		if (putBattleshipIsAllowed(player2, battleshipPos, &i))
			++i;
	}
}

void attackPhase(Player *player1, Player *player2)
{
	printf("Attack a coordinate\n");

	int turn = 0;

	while (true)
	{
		turn++;
		playerTurn(&turn, player1, player2);

		if (isGameOver(player1, player2))
			break;

	}
}

void startGame()
{
	Player player1, player2;
	BattleshipPosition battleshipPos;

	int x, y = 0;
	char pos;

	initMap(&player1, "map.txt");
	memcpy(&player2, &player1, sizeof(player1));

	printf("\e[1;1H\e[2J");

	enterPlayerNamePhase(&player1, &player2);
	putBattleshipPhase(&player1, &player2, &battleshipPos);
	attackPhase(&player1, &player2);
}

void loadHomePage() 
{
	int input; 

	printf("BATTLESHIP\n");
	printf("1. Play game\n");
	printf("2. Exit\n");
	printf("Enter a number: ");

	scanf("%d", &input); getchar();

	switch(input) {
		case 1:
			startGame();
			break;
		case 2: exit(EXIT_SUCCESS);
		default: loadHomePage();
	}
}