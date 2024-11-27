#pragma once

#include "block.h"

Block::Block()
{
    dx = 0;
    rotate = false;
}

bool Block::checkValidMove(Point *t_currentBlock, int t_gameGrid[][WIDTH])
{
    for (int tileNum = 0; tileNum < MAX_TILES; tileNum++)
    {
        if (t_currentBlock[tileNum].x < 0 || t_currentBlock[tileNum].x >= WIDTH || t_currentBlock[tileNum].y >= LENGTH)
        {
            return false;
        }
        else if (t_gameGrid[t_currentBlock[tileNum].y][t_currentBlock[tileNum].x])
        {
            return false;
        }
    }

    return true;
};

void Block::blockRotation(Point* t_currentBlock, Point* t_backupBlock, int t_gameGrid[][WIDTH])
{
    if (rotate)
    {
        Point centreRotation = t_currentBlock[1]; //center of rotation
        for (int tileNum = 0; tileNum < MAX_TILES; tileNum++)
        {
            int x = t_currentBlock[tileNum].y - centreRotation.y;
            int y = t_currentBlock[tileNum].x - centreRotation.x;
            t_currentBlock[tileNum].x = centreRotation.x - x;
            t_currentBlock[tileNum].y = centreRotation.y + y;
        }
        if (checkValidMove(t_currentBlock, t_gameGrid) == false)
        {
            for (int tileNum = 0; tileNum < MAX_TILES; tileNum++)
            {
                t_currentBlock[tileNum] = t_backupBlock[tileNum];
            }
        }
    }
}

void Block::blockMove(Point* t_currentBlock, Point* t_backupBlock, int t_gameGrid[][WIDTH])
{
    for (int tileNum = 0; tileNum < MAX_TILES; tileNum++)
    {
        t_backupBlock[tileNum] = t_currentBlock[tileNum];
        t_currentBlock[tileNum].x += dx;
    }
    if (checkValidMove(t_currentBlock, t_gameGrid) == false)
    {
        for (int tileNum = 0; tileNum < MAX_TILES; tileNum++)
        {
            t_currentBlock[tileNum] = t_backupBlock[tileNum];
        }
    }
}