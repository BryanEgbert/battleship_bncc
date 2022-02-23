#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "battleship.h"

typedef struct Ship
{
	int width;
	int height;
}Ship;

typedef struct Player
{
	char name[50];
	Ship ships[5];
}Player;

static Player player1, player2;
static char map[MAP_Y][MAP_X]; 

void run() 
{
	loadHomePage();
	start_game();
}

void init_map()
{
	FILE *file = fopen("map.txt", "r");
	if (file == NULL)
	{
		perror("Something's wrong when loading the map\n");
		exit(EXIT_FAILURE);
	}


	for (int i = 0; !feof(file); ++i)
		fgets(map[i], MAX_BYTE, file);

	fclose(file);

}

void start_game() {
	init_map();

	printf("Enter player 1 name (max 50 chars.): ");
	scanf("%[^\n]", player1.name);

	printf("Enter player 2 name (max 50 chars.): ");
	scanf("%[^\n]", player2.name);

	while(true) {
		render();
	}
}

void loadHomePage() 
{
	int input; 

	printf("BATTLESHIP\n");
	printf("1. Play game\n");
	printf("2. Exit\n");
	printf("Enter a number: ");

	scanf("%d", &input);

	switch(input) {
		case 1: break;
		case 2: exit(EXIT_SUCCESS);
		default: loadHomePage();
	}
}

void render() {
}



