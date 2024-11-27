#pragma once

#include <SFML/Graphics.hpp>
#include <time.h>
#include "block.h"
#include "constants.cpp"

using namespace sf;

class Game {
public:
    Game();
    void update(sf::RenderWindow& t_window);
    void draw(sf::RenderWindow& t_window);
    void drawTiles(int t_posX, int t_posY, int t_tile, sf::Sprite t_tileSprite, sf::RenderWindow& t_window);
    void setupSprites();
    void processInputs(sf::RenderWindow& t_window);
    void checkLines();
    void trackTimer();
private:
    Block block;
    Clock clock;
    Sprite tiles, background, frame;
    Texture tilesTexture, backgroundTexture, frameTexture;
    int colorNum = 1;
    float timer = 0, delay = 0.3;
};