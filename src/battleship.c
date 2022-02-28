#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "battleship.h"

void run() 
{
	loadHomePage();
	startGame();
}

void initMap(Player* player)
{
	FILE *file = fopen("map.txt", "r");

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

void initPlayerInfo(Player* player)
{
	printf("Enter player 1 name (max 50 chars.): ");
	scanf("%[^\n]", player->name);
	getchar();

	player->shipHitCount = 0;
	player->ships[0] = 2;
	player->ships[1] = 3;
	player->ships[2] = 4;
	player->ships[3] = 5;
}

void putBattleship(Player* player)
{
	printf("%s turn\n", player->name);

	int x, y, i = 0;
	char pos;
	bool shipExits;

	while(i < MAX_BATTLESHIP)
	{
		shipExits = false;

		printf("Battleship lenght: %d\n", player->ships[i]);

		displayMap(player, BATTLESHIP_MAP);

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
				if(player->battleshipMap[y][j] == '@' || player->battleshipMap[y][j] == '#')
					shipExits = true;

			if(shipExits)
			{
				printf("There's existing ship over there\n");
				continue;
			}

			for (int j = x; j < player->ships[i] + x; ++j)
				player->battleshipMap[y][j] = '@';
		}
		else
		{
			for (int j = y; j < player->ships[i] + y; ++j)
				if (player->battleshipMap[j][x] == '@' || player->battleshipMap[y][j] == '#')
					shipExits = true;

			if(shipExits)
			{
				printf("There's existing ship over there\n");
				continue;
			}

			for(int j = y; j < player->ships[i] + y; ++j)
				player->battleshipMap[j][x] = '@';
		}

		++i;
	}
}

void startGame() {
	Player player1, player2;

	initMap(&player1);
	memcpy(&player2, &player1, sizeof(player1));

	initPlayerInfo(&player1);
	initPlayerInfo(&player2);

	printf("Put Your Battleships\n");
	putBattleship(&player1);
	putBattleship(&player2);

	printf("Attack a coordinate\n");

	int turn = 0;

	while(true) 
	{
		turn++;

		playerTurn(&turn, &player1, &player2);

		if(player1.shipHitCount == TOTAL_BATTLESHIP_LEN)
		{
			printf("%s wins\n", player1.name);
			break;
		}
		else if(player2.shipHitCount == TOTAL_BATTLESHIP_LEN)
		{
			printf("%s wins", player2.name);
			break;
		}
	}
}

void playerTurn(int* turn, Player* player1, Player* player2)
{
	int x, y;

	if(*turn % 2 != 0)
	{
		displayMap(player1, EMPTY_MAP);

		printf("Player 1's turn\n");

		printf("Choose Y coordinate: ");
		scanf("%d", &y);

		printf("Choose X coordinate: ");
		scanf("%d", &x);

		if(player2->battleshipMap[y][x] == '@')
		{
			player1->emptyMap[y][x] ='O';
			player1->shipHitCount++;
			printf("You hit a ship\n");
		}
		else
			player1->emptyMap[y][x] = 'X';
	}
	else
	{
		displayMap(player2, EMPTY_MAP);

		printf("Player 2's turn\n");

		printf("Choose Y coordinate: ");
		scanf("%d", &y);

		printf("Choose X coordinate: ");
		scanf("%d", &x);

		if (player1->battleshipMap[y][x] == '@')
		{
			player2->emptyMap[y][x] = 'O';
			player2->shipHitCount++;
			printf("You hit a ship\n");
		}
		else
			player2->emptyMap[y][x] = 'X';
	}
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