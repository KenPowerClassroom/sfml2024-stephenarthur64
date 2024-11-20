#include "pch.h"

#include "../16_SFML_Games/block.cpp"

TEST(Block, checkValidMove)
{
	Block block;

    for (int tileNum = 0; tileNum < MAX_TILES; tileNum++)
    {
        backupBlock[tileNum] = currentBlock[tileNum];
        currentBlock[tileNum].x += 1;
    }

    EXPECT_EQ(true, block.checkValidMove());
}