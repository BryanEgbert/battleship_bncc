#include <gtest/gtest.h>

extern "C"
{
	#include <string.h>
	#include <unistd.h>
	#include "../src/battleship.h"
}

TEST(battleshipTest, initMapTest)
{
	char expectedBattleshipMap[11][11] = {
		{'#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
		{'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
		{'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
		{'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
		{'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
		{'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
		{'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
		{'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
		{'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
		{'#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
	};

	Player player;
	initMap(&player, "../../map.txt");

	for (int i = 0; i < MAP_Y; ++i)
	{
		for (int j = 0; j < MAP_X; ++j)
		{
			ASSERT_EQ(player.battleshipMap[i][j], expectedBattleshipMap[i][j]) << "battleshipMap differ at" << i << ' ' << j;
			ASSERT_EQ(player.emptyMap[i][j], expectedBattleshipMap[i][j]) << "emptyMap differ at" << i << ',' << j;
		}
	};
}

TEST(battleshipTest, initPlayerInfoTest)
{
	Player player;
	const char* name = "john";

	int startingBattleshipLen = 2;
	initPlayerInfo(&player, name);

	EXPECT_EQ(strcmp(player.name, name), 0) << "Player name is not the same";
	EXPECT_EQ(player.shipHitCount, 0) << "Player ship hit count is not 0";
	for(int i = 0; i < MAX_BATTLESHIP; ++i)
	{
		ASSERT_EQ(player.ships[i], startingBattleshipLen) << "Battleship initialization is not as expected";
		startingBattleshipLen++;
	}
}

// Need to press enter when this test run die to buffering
TEST(battleshipTest, putBattleshipAllowanceTest)
{
	Player player;
	BattleshipPosition battleshipPos;
	int index = 0;

	// Declare values
	battleshipPos.coordinate.x = 1;
	battleshipPos.coordinate.y = 1;
	battleshipPos.pos = 'v';
	initMap(&player, "../../map.txt");
	initPlayerInfo(&player, "john");

	_Bool output = putBattleshipIsAllowed(&player, &battleshipPos, &index);

	EXPECT_EQ(output, 1) << "Function output is not as expected";
	EXPECT_EQ(player.battleshipMap[battleshipPos.coordinate.y][battleshipPos.coordinate.x], '@') << "Battleship parts is not inserted as expected";
	EXPECT_EQ(player.battleshipMap[battleshipPos.coordinate.y + 1][battleshipPos.coordinate.x], '@') << "Battleship parts is not inserted as expected";

	battleshipPos.coordinate.x = 0;
	battleshipPos.coordinate.y = 0;
	battleshipPos.pos = 'v';

	output = putBattleshipIsAllowed(&player, &battleshipPos, &index);

	EXPECT_EQ(output, 0) << "Function output is not as expected";
}

TEST(battleshipTest, playerTurnTest)
{
	Player player1, player2;
	Coordinate coordinate1{.x = 1, .y = 1}, coordinate2{.x = 1, .y = 3};

	char battleshipMapSample[11][11] = {
		{'#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
		{'#', '@', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
		{'#', '@', ' ', ' ', ' ', ' ', '@', ' ', ' ', '#'},
		{'#', ' ', ' ', ' ', ' ', ' ', '@', ' ', ' ', '#'},
		{'#', ' ', '@', '@', '@', ' ', '@', ' ', ' ', '#'},
		{'#', ' ', ' ', ' ', ' ', ' ', '@', ' ', ' ', '#'},
		{'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
		{'#', ' ', ' ', ' ', '@', '@', '@', '@', '@', '#'},
		{'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
		{'#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
	};

	char emptyMapSample[11][11] = {
		{'#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
		{'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
		{'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
		{'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
		{'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
		{'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
		{'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
		{'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
		{'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
		{'#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
	};

	// Initialize values
	for(int i = 0; i < 11; ++i)
	{
		strcpy(player1.battleshipMap[i], battleshipMapSample[i]);
		strcpy(player1.emptyMap[i], emptyMapSample[i]);
	}

	strcpy(player1.name, "john");
	player1.shipHitCount = 0;
	player1.ships[0] = 2;
	player1.ships[1] = 3;
	player1.ships[2] = 4;
	player1.ships[3] = 5;

	strcpy(player2.name, "johni");
	player2.shipHitCount = 0;
	player2.ships[0] = 2;
	player2.ships[1] = 3;
	player2.ships[2] = 4;
	player2.ships[3] = 5;

	memcpy(&player2, &player1, sizeof(player1));

	// Test
	for(int i = 0; i < 2; ++i)
	{
		hitCoordinate(&i, &player1, &player2, &coordinate1);
	}

	EXPECT_EQ(player1.emptyMap[coordinate1.y][coordinate1.x], 'O') << "Chars is not inserted to empty map";
	EXPECT_EQ(player2.emptyMap[coordinate1.y][coordinate1.x], 'O') << "Chars is not inserted to empty map";

	for (int i = 0; i < 2; ++i)
	{
		hitCoordinate(&i, &player1, &player2, &coordinate2);
	}

	EXPECT_EQ(player1.emptyMap[coordinate2.y][coordinate2.x], 'X') << "Chars is not inserted to empty map";
	EXPECT_EQ(player2.emptyMap[coordinate2.y][coordinate2.x], 'X') << "Chars is not inserted to empty map";
}

TEST(battleshipTest, isGameOverTest)
{
	Player player1 {.shipHitCount = 14}, player2 {.shipHitCount = 13};
	strcpy(player1.name, "johni");
	strcpy(player2.name, "john");

	_Bool output = isGameOver(&player1, &player2);
	ASSERT_EQ(output, 1);

	player1.shipHitCount = 1; 
	player2.shipHitCount = 13;
	output = isGameOver(&player1, &player2);
	ASSERT_EQ(output, 0);
}

int main(int argc, char **argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}