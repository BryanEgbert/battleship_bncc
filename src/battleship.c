#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "battleship.h"

typedef struct Player
{
	char name[50];
	int ships[MAX_BATTLESHIP];
	char map[MAP_Y][MAP_X];
}Player;

static Player player1 = {.ships = {2, 3, 4, 5}}, player2 = {.ships = {2, 3, 4, 5}};

void run() 
{
	loadHomePage();
	startGame();
}

void initMap()
{
	FILE *file = fopen("map.txt", "r");
	if (file == NULL)
	{
		perror("Something's wrong when loading the map\n");
		exit(EXIT_FAILURE);
	}

	for (int i = 0; !feof(file); ++i)
		fscanf(file, "%[^\n]\n", player1.map[i]);

	for(int i = 0; i < MAP_Y; ++i)
		strcpy(player2.map[i], player1.map[i]);

	fclose(file);
}

void displayMap(Player* player)
{
	for(int i = 0; i < MAP_Y; ++i)
	{
		for(int j = 0; j < MAP_X; ++j)
			printf("%c", (*player).map[i][j]);
		printf("\n");
	}
}


void putBattleship(Player* player)
{

	printf("%s turn\n", player->name);
	int x, y, i = 0;
	char pos;
	bool shipExits = false;

	while(i < MAX_BATTLESHIP)
	{
		shipExits = false;

		printf("Lenght: %d\n", player->ships[i]);

		displayMap(player);

		printf("Place vertical or horizontal (v/h): ");
		scanf("%c", &pos);
		getchar();

		while (pos != 'v' && pos != 'h')
		{
			printf("False\nPlace vertical or horizontal (v/h): ");			
			scanf("%c", &pos); getchar();
		}

		printf("Choose Y coordinate (1 - %d): ", MAP_Y - 2);
		scanf("%d", &y);

		while(y < 1 || y > MAP_Y - 2)
		{
			printf("Choose Y coordinate (1 - %d): ", MAP_Y - 2);
			scanf("%d", &y);
		}

		printf("Choose X coordinate (1 - %d): ", MAP_X - 2);
		scanf("%d", &x); getchar();

		while (x < 1 || x > MAP_X - 2)
		{
			printf("Choose X coordinate (1 - %d): ", MAP_X - 2);
			scanf("%d", &x);
		}

		if(pos == 'h')
		{
			for(int j = x; j < player->ships[i] + x; ++j)
				if(player->map[y][j] == '@' || player->map[y][j] == '#')
					shipExits = true;

			if(shipExits)
			{
				printf("There's existing ship over there\n");
				continue;
			}

			for (int j = x; j < player->ships[i] + x; ++j)
				player->map[y][j] = '@';
		}
		else
		{
			for (int j = y; j < player->ships[i] + y; ++j)
				if (player->map[j][x] == '@' || player->map[y][j] == '#')
					shipExits = true;

			if(shipExits)
			{

				printf("There's existing ship over there\n");
				continue;
			}

			for(int j = y; j < player->ships[i] + y; ++j)
				player->map[j][x] = '@';
		}

		++i;
	}
}

void getPlayerName()
{
	printf("Enter player 1 name (max 50 chars.): ");
	scanf("%[^\n]", player1.name); getchar();

	printf("Enter player 2 name (max 50 chars.): ");
	scanf("%[^\n]", player2.name); getchar();
}

void startGame() {
	initMap();
	getPlayerName();
	printf("Put Your Battleships\n");
	putBattleship(&player1);
	putBattleship(&player2);

	printf("Player 1 map\n");
	displayMap(&player1);

	printf("player 2 map\n");
	displayMap(&player2);
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
			break;
		case 2: exit(EXIT_SUCCESS);
		default: loadHomePage();
	}
}

void render() {
}



