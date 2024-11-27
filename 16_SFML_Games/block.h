#pragma once
#include "constants.cpp"

class Block {
public:
    Block();
    void blockRotation(Point* t_currentBlock, Point* t_backupBlock, int t_gameGrid[][WIDTH]);
    void blockMove(Point* t_currentBlock, Point* t_backupBlock, int t_gameGrid[][WIDTH]);
    bool checkValidMove(Point* t_currentBlock, int t_gameGrid[][WIDTH]);
    void setDirectionX(int t_newDx) { dx = t_newDx; }
    void setRotation(bool t_newRotate) { rotate = t_newRotate; }
private:
    int dx;
    bool rotate;
};