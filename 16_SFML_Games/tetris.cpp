#pragma once

#include "tetris.h"

Point currentBlock[MAX_TILES], backupBlock[MAX_TILES];
int gameGrid[LENGTH][WIDTH] = { 0 };

using namespace sf;

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


Game::Game()
{
    setupSprites();
}

void Game::update(sf::RenderWindow& t_window)
{
    float time = clock.getElapsedTime().asSeconds();
    clock.restart();
    timer += time;

    processInputs(t_window);

    //// <- Move -> ///
    block.blockMove(currentBlock, backupBlock, gameGrid);

    //////Rotate//////
    block.blockRotation(currentBlock, backupBlock, gameGrid);

    ///////Tick//////
    trackTimer();

    ///////check lines//////////
    checkLines();

    /////////draw//////////
    draw(t_window);
}

void Game::drawTiles(int t_posX, int t_posY, int t_tile, sf::Sprite t_tileSprite, sf::RenderWindow& t_window)
{
    t_tileSprite.setTextureRect(IntRect(t_tile, 0, TILE_SIZE, TILE_SIZE));
    t_tileSprite.setPosition(t_posX, t_posY);
    t_tileSprite.move(OFFSET_X, OFFSET_Y);
    t_window.draw(t_tileSprite);
}

void Game::draw(sf::RenderWindow &t_window)
{
    t_window.clear(Color::White);
    t_window.draw(background);

    for (int lengthCount = 0; lengthCount < LENGTH; lengthCount++)
    {
        for (int widthCount = 0; widthCount < WIDTH; widthCount++)
        {
            if (gameGrid[lengthCount][widthCount] == 0)
            {
                continue;
            }
            drawTiles(widthCount * TILE_SIZE,
                lengthCount * TILE_SIZE,
                gameGrid[lengthCount][widthCount] * TILE_SIZE,
                tiles,
                t_window);
        }
    }

    for (int tileNum = 0; tileNum < MAX_TILES; tileNum++)
    {
        drawTiles(currentBlock[tileNum].x * TILE_SIZE,
            currentBlock[tileNum].y * TILE_SIZE,
            colorNum * TILE_SIZE,
            tiles,
            t_window);
    }

    t_window.draw(frame);
    t_window.display();
}

void Game::setupSprites()
{
    tilesTexture.loadFromFile("images/tetris/tiles.png");
    backgroundTexture.loadFromFile("images/tetris/background.png");
    frameTexture.loadFromFile("images/tetris/frame.png");
    tiles.setTexture(tilesTexture);
    background.setTexture(backgroundTexture); 
    frame.setTexture(frameTexture);
}

void Game::processInputs(sf::RenderWindow &t_window)
{
    Event inputEvent;
    while (t_window.pollEvent(inputEvent))
    {
        if (inputEvent.type == Event::Closed)
        {
            t_window.close();
        }

        if (inputEvent.type == Event::KeyPressed)
        {
            if (inputEvent.key.code == Keyboard::Up)
            {
                block.setRotation(true);
            }
            else if (inputEvent.key.code == Keyboard::Left)
            {
               block.setDirectionX(-1);
            }
            else if (inputEvent.key.code == Keyboard::Right)
            {
                block.setDirectionX(1);
            }
        }
    }
    if (Keyboard::isKeyPressed(Keyboard::Down))
    {
        delay = 0.05; // Increases Movement Speed
    }
}

void Game::checkLines()
{
    int currentLine = LENGTH - 1;
    for (int lengthCount = LENGTH - 1; lengthCount > 0; lengthCount--)
    {
        int count = 0;
        for (int widthCount = 0; widthCount < WIDTH; widthCount++)
        {
            if (gameGrid[lengthCount][widthCount])
            {
                count++;
            }
            gameGrid[currentLine][widthCount] = gameGrid[lengthCount][widthCount];
        }
        if (count < WIDTH)
        {
            currentLine--;
        }
    }

    block.setDirectionX(0);
    block.setRotation(false);
    delay = 0.3;
}

void Game::trackTimer()
{
    if (timer > delay)
    {
        for (int tileNum = 0; tileNum < MAX_TILES; tileNum++)
        {
            backupBlock[tileNum] = currentBlock[tileNum];
            currentBlock[tileNum].y += 1;
        }

        if (block.checkValidMove(currentBlock, gameGrid) == false)
        {
            for (int tileNum = 0; tileNum < MAX_TILES; tileNum++)
            {
                gameGrid[backupBlock[tileNum].y][backupBlock[tileNum].x] = colorNum;
            }

            colorNum = 1 + (rand() % MAX_FIGURES);
            int figureType = rand() % MAX_FIGURES;
            for (int tileNum = 0; tileNum < MAX_TILES; tileNum++)
            {
                currentBlock[tileNum].x = figures[figureType][tileNum] % 2;
                currentBlock[tileNum].y = figures[figureType][tileNum] / 2;
            }
        }

        timer = 0;
    }
}

int tetris()
{
    srand(time(0));     
    RenderWindow window(VideoMode(320, 480), "The Game!");

    Game tetrisGame;

    while (window.isOpen())
    {
        tetrisGame.update(window);
    }
    return 0;
}




