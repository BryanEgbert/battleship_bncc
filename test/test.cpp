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