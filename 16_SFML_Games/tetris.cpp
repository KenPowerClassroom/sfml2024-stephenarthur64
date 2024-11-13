#include <SFML/Graphics.hpp>
#include <time.h>
using namespace sf;

const int LENGTH = 20;
const int WIDTH = 10;
const int TILE_SIZE = 18;
const int MAX_TILES = 4;
const int MAX_FIGURES = 7;
const int OFFSET_X = 28;
const int OFFSET_Y = 31;

int gameGrid[LENGTH][WIDTH] = {0};

Sprite tiles, background, frame;
Texture tilesTexture, backgroundTexture, frameTexture;
bool rotate = false;
int dx = 0;
int colorNum = 1;
float timer = 0, delay = 0.3;


struct Point
{
    int x,y;
} currentBlock[MAX_TILES], backupBlock[MAX_TILES];

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

bool checkValidMove()
{
   for (int tileNum=0;tileNum< MAX_TILES;tileNum++)
   {
       if (currentBlock[tileNum].x < 0 || currentBlock[tileNum].x >= WIDTH || currentBlock[tileNum].y >= LENGTH) 
       {
           return false;
       }
       else if (gameGrid[currentBlock[tileNum].y][currentBlock[tileNum].x]) 
       {
           return false;
       }
   }

   return true;
};

void drawTiles(int t_posX, int t_posY, int t_tile, sf::Sprite t_tileSprite, sf::RenderWindow& t_window)
{
    t_tileSprite.setTextureRect(IntRect(t_tile, 0, TILE_SIZE, TILE_SIZE));
    t_tileSprite.setPosition(t_posX, t_posY);
    t_tileSprite.move(OFFSET_X, OFFSET_Y);
    t_window.draw(t_tileSprite);
}

void draw(sf::Sprite t_tileSprite, sf::RenderWindow &t_window, sf::Sprite t_background, int t_color, sf::Sprite t_frame)
{
    t_window.clear(Color::White);
    t_window.draw(t_background);

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
                t_tileSprite,
                t_window);
        }
    }

    for (int tileNum = 0; tileNum < MAX_TILES; tileNum++)
    {
        drawTiles(currentBlock[tileNum].x * TILE_SIZE,
            currentBlock[tileNum].y * TILE_SIZE,
            t_color * TILE_SIZE,
            t_tileSprite,
            t_window);
    }

    t_window.draw(t_frame);
    t_window.display();
}

void setupSprites()
{
    tilesTexture.loadFromFile("images/tetris/tiles.png");
    backgroundTexture.loadFromFile("images/tetris/background.png");
    frameTexture.loadFromFile("images/tetris/frame.png");
    tiles.setTexture(tilesTexture);
    background.setTexture(backgroundTexture); 
    frame.setTexture(frameTexture);
}

void processInputs(sf::RenderWindow &t_window)
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
               rotate = true;
            }
            else if (inputEvent.key.code == Keyboard::Left)
            {
               dx = -1;
            }
            else if (inputEvent.key.code == Keyboard::Right)
            {
                dx = 1;
            }
        }
    }
}

void checkLines()
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

    dx = 0;
    rotate = 0;
    delay = 0.3;
}

void blockRotation()
{
    if (rotate)
    {
        Point centreRotation = currentBlock[1]; //center of rotation
        for (int tileNum = 0; tileNum < MAX_TILES; tileNum++)
        {
            int x = currentBlock[tileNum].y - centreRotation.y;
            int y = currentBlock[tileNum].x - centreRotation.x;
            currentBlock[tileNum].x = centreRotation.x - x;
            currentBlock[tileNum].y = centreRotation.y + y;
        }
        if (checkValidMove() == false)
        {
            for (int tileNum = 0; tileNum < MAX_TILES; tileNum++)
            {
                currentBlock[tileNum] = backupBlock[tileNum];
            }
        }
    }
}

int tetris()
{
    srand(time(0));     

    RenderWindow window(VideoMode(320, 480), "The Game!");
    setupSprites();
 
    Clock clock;

    while (window.isOpen())
    {
        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        timer += time;

        processInputs(window);

        if (Keyboard::isKeyPressed(Keyboard::Down))
        {
            delay = 0.05; // Increases Movement Speed
        }

        //// <- Move -> ///
        for (int tileNum = 0; tileNum < MAX_TILES; tileNum++)
        {
            backupBlock[tileNum] = currentBlock[tileNum];
            currentBlock[tileNum].x += dx;
        }
        if (checkValidMove() == false)
        {
            for (int tileNum = 0; tileNum < MAX_TILES; tileNum++)
            {
                currentBlock[tileNum] = backupBlock[tileNum];
            }
        }

        //////Rotate//////
        blockRotation();

        ///////Tick//////
        if (timer > delay)
        {
            for (int tileNum = 0; tileNum < MAX_TILES; tileNum++)
            {
                backupBlock[tileNum] = currentBlock[tileNum];
                currentBlock[tileNum].y += 1;
            }

            if (checkValidMove() == false)
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

        ///////check lines//////////
        checkLines();

        /////////draw//////////
        draw(tiles, window, background, colorNum, frame);
    }
    return 0;
}




