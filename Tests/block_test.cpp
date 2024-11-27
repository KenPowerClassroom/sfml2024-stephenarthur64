#include "pch.h"

#include "../16_SFML_Games/block.h"
#include "../16_SFML_Games/block.cpp"

Block block;
Point currentBlock[MAX_TILES], backupBlock[MAX_TILES];
int gameGrid[LENGTH][WIDTH] = { 0 };
int figures[MAX_FIGURES][MAX_TILES] =
{
    1,3,5,7, // I
    2,4,5,7, // Z
    3,5,4,6, // S
    3,5,4,7, // T
    2,3,5,7, // L
    3,5,7,6, // J
    2,3,4,5, // O
};

TEST(Block, checkingValidMove)
{
    // Building scenario to be tested
    for (int tileNum = 0; tileNum < MAX_TILES; tileNum++)
    {
        currentBlock[tileNum].x = figures[0][tileNum] % 2;
        currentBlock[tileNum].y = figures[0][tileNum] / 2;
        backupBlock[tileNum] = currentBlock[tileNum];
        currentBlock[tileNum].x += 1;
    }

    EXPECT_EQ(true, block.checkValidMove(currentBlock, gameGrid));
}

TEST(Block, checkingInvalidMove)
{
    // Building scenario to be tested
    for (int tileNum = 0; tileNum < MAX_TILES; tileNum++)
    {
        currentBlock[tileNum].x = figures[0][tileNum] % 2;
        currentBlock[tileNum].y = figures[0][tileNum] / 2;
        backupBlock[tileNum] = currentBlock[tileNum];
        currentBlock[tileNum].x -= 10;
    }

    EXPECT_EQ(false, block.checkValidMove(currentBlock, gameGrid));
}

TEST(Block, blockMove)
{
    // Building scenario to be tested
    for (int tileNum = 0; tileNum < MAX_TILES; tileNum++)
    {
        currentBlock[tileNum].x = figures[0][tileNum] % 2;
        currentBlock[tileNum].y = figures[0][tileNum] / 2;
        backupBlock[tileNum] = currentBlock[tileNum];
    }

    block.setDirectionX(2);
    block.blockMove(currentBlock, backupBlock, gameGrid);

    EXPECT_EQ(3, currentBlock[0].x);
    EXPECT_EQ(3, currentBlock[1].x);
    EXPECT_EQ(3, currentBlock[2].x);
    EXPECT_EQ(3, currentBlock[3].x);
}

TEST(Block, blockRotation)
{
    // Building scenario to be tested
    for (int tileNum = 0; tileNum < MAX_TILES; tileNum++)
    {
        currentBlock[tileNum].x = figures[0][tileNum] % 2;
        currentBlock[tileNum].y = figures[0][tileNum] / 2;
        backupBlock[tileNum] = currentBlock[tileNum];
    }

    block.setRotation(true);
    block.blockRotation(currentBlock, backupBlock, gameGrid);

    EXPECT_EQ(1, currentBlock[0].x);
    EXPECT_EQ(0, currentBlock[0].y);

    EXPECT_EQ(1, currentBlock[1].y);

    EXPECT_EQ(2, currentBlock[2].y);

    EXPECT_EQ(3, currentBlock[3].y);
}

