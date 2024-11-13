#include <SFML/Graphics.hpp>
#include <time.h>
using namespace sf;

const int LENGTH = 20;
const int WIDTH = 10;

int gameGrid[LENGTH][WIDTH] = {0};

struct Point
{
    int x,y;
} currentBlock[4], backupBlock[4];

int figures[7][4] =
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
   for (int i=0;i<4;i++)
   {
       if (currentBlock[i].x < 0 || currentBlock[i].x >= WIDTH || currentBlock[i].y >= LENGTH) 
       {
           return false;
       }
       else if (gameGrid[currentBlock[i].y][currentBlock[i].x]) 
       {
           return false;
       }
   }

   return true;
};


int tetris()
{
    srand(time(0));     

    RenderWindow window(VideoMode(320, 480), "The Game!");

    Texture tilesTexture,backgroundTexture,frameTexture;
    tilesTexture.loadFromFile("images/tetris/tiles.png");
    backgroundTexture.loadFromFile("images/tetris/background.png");
    frameTexture.loadFromFile("images/tetris/frame.png");

    Sprite tiles(tilesTexture), background(backgroundTexture), frame(frameTexture);

    int dx=0; 
    bool rotate = false; 
    int colorNum=1;
    float timer=0,delay=0.3; 

    Clock clock;

    while (window.isOpen())
    {
        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        timer+=time;

        Event inputEvent;
        while (window.pollEvent(inputEvent))
        {
            if (inputEvent.type == Event::Closed)
            {
                window.close();
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

    if (Keyboard::isKeyPressed(Keyboard::Down)) 
    {
        delay = 0.05; // Increases Movement Speed
    }

    //// <- Move -> ///
    for (int tileNum=0;tileNum<4;tileNum++)  
    { 
        backupBlock[tileNum]=currentBlock[tileNum]; 
        currentBlock[tileNum].x+=dx; 
    }
    if (checkValidMove() == false) 
    {
        for (int i = 0; i < 4; i++) 
        {
            currentBlock[i] = backupBlock[i];
        }
    }

    //////Rotate//////
    if (rotate)
      {
        Point centreRotation = currentBlock[1]; //center of rotation
        for (int tileNum=0;tileNum<4;tileNum++)
        {
            int x = currentBlock[tileNum].y-centreRotation.y;
            int y = currentBlock[tileNum].x-centreRotation.x;
            currentBlock[tileNum].x = centreRotation.x - x;
            currentBlock[tileNum].y = centreRotation.y + y;
        }
        if (checkValidMove() == false) 
        {
            for (int i = 0; i < 4; i++) 
            {
                currentBlock[i] = backupBlock[i];
            }
        }
      }

    ///////Tick//////
    if (timer>delay)
      {
        for (int tileNum=0;tileNum<4;tileNum++) 
        { 
            backupBlock[tileNum]=currentBlock[tileNum]; 
            currentBlock[tileNum].y+=1; 
        }

        if (checkValidMove() == false)
        {
            for (int tileNum=0;tileNum<4;tileNum++) 
            {
                gameGrid[backupBlock[tileNum].y][backupBlock[tileNum].x] = colorNum;
            }

            colorNum = 1 + (rand()%7);
            int figureType=rand()%7;
            for (int tileNum=0;tileNum<4;tileNum++)
            {
                currentBlock[tileNum].x = figures[figureType][tileNum] % 2;
                currentBlock[tileNum].y = figures[figureType][tileNum] / 2;
            }
        }

         timer=0;
      }

    ///////check lines//////////
    int currentLine=LENGTH-1;
    for (int lengthCount=LENGTH-1;lengthCount>0;lengthCount--)
    {
        int count=0;
        for (int widthCount=0;widthCount<WIDTH;widthCount++)
        {
            if (gameGrid[lengthCount][widthCount]) 
            {
                count++;
            }
            gameGrid[currentLine][widthCount]=gameGrid[lengthCount][widthCount];
        }
        if (count<WIDTH) 
        {
            currentLine--;
        }
    }

    dx=0; 
    rotate=0; 
    delay=0.3;

    /////////draw//////////
    window.clear(Color::White);    
    window.draw(background);
          
    for (int lengthCount=0;lengthCount<LENGTH;lengthCount++)
    {
        for (int widthCount = 0; widthCount < WIDTH; widthCount++)
        {
            if (gameGrid[lengthCount][widthCount] == 0) 
            {
                continue;
            }
            tiles.setTextureRect(IntRect(gameGrid[lengthCount][widthCount] * 18, 0, 18, 18));
            tiles.setPosition(widthCount * 18, lengthCount * 18);
            tiles.move(28, 31); //offset
            window.draw(tiles);
        }
    }

    for (int tileNum=0;tileNum<4;tileNum++)
      {
        tiles.setTextureRect(IntRect(colorNum*18,0,18,18));
        tiles.setPosition(currentBlock[tileNum].x*18,currentBlock[tileNum].y*18);
        tiles.move(28,31); //offset
        window.draw(tiles);
      }

    window.draw(frame);
    window.display();
    }

    return 0;
}
