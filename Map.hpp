#ifndef MAP_HPP
#define MAP_HPP

#include <iostream>
#include <random>
#include <chrono>
#include <vector>
#include <SFML/Graphics.hpp>
using namespace sf;

#include "Tile.hpp"
#include "Coord.hpp"

using namespace std;
using namespace chrono;

class Map {
    public:
        high_resolution_clock::time_point oldTime;

        const double TICK_SPEED = 0.14;

        const unsigned int LEFT = 1;
        const unsigned int UP = 2;
        const unsigned int RIGHT = 3;
        const unsigned int DOWN = 4;

        bool gameOver = false;
        Map();
        
        void update();
        void reset();
        void draw(RenderTarget& window);

        void setDirection(int d);
        int getDirection() const;

        bool foodInSnake() const;

        unsigned int getSnakeSize() const;
    private:
        Tile screenTiles[Tile::SCREEN_WIDTH][Tile::SCREEN_HEIGHT];

        unsigned int pastDirection = LEFT;
        unsigned int direction = LEFT;
        vector<Coord> snakeBody;

        Coord head = Coord(Tile::SCREEN_WIDTH/2 + Tile::SCREEN_WIDTH/4, Tile::SCREEN_HEIGHT/2 - 1);
        Coord food = Coord(Tile::SCREEN_WIDTH/2 - Tile::SCREEN_WIDTH/4, Tile::SCREEN_HEIGHT/2 - 1);
};

Map::Map() {
    srand(time(NULL));
    rand();
    oldTime = high_resolution_clock::now();
    for(int i = 0; i < Tile::SCREEN_WIDTH; i++) {
        for(int j = 0; j < Tile::SCREEN_HEIGHT; j++) {
            screenTiles[i][j] = Tile(i, j);
        }
    }

    snakeBody.push_back(head);
    screenTiles[head.x][head.y].setType(1);
    screenTiles[food.x][food.y].setType(2);
}

void Map::update() {
    high_resolution_clock::time_point currentTime = high_resolution_clock::now();
    if((currentTime - oldTime).count() > TICK_SPEED * 1000000000 && !gameOver) {
        pastDirection = direction;
        int x = snakeBody.at(0).x;
        int y = snakeBody.at(0).y;

        Coord newCoord = Coord(x,y);
        if(direction == LEFT) {
            newCoord.x -= 1;
        } else if(direction == UP) {
            newCoord.y -= 1;
        } else if(direction == RIGHT) {
            newCoord.x += 1;
        } else if(direction == DOWN) {
            newCoord.y += 1;
        }

        bool hitEdges = !(newCoord.x > -1 && newCoord.y > -1 && newCoord.x < Tile::SCREEN_WIDTH && newCoord.y < Tile::SCREEN_HEIGHT);
        bool hitSelf = false;
        for(int i = 1; i < snakeBody.size(); i++) {
            if(newCoord.equals(snakeBody.at(i))) {
                hitSelf = true;
                break;
            }
        }

        bool deleteEnd = true;

        if(newCoord.equals(food)) {
            deleteEnd = false;
            food.x = rand() % Tile::SCREEN_WIDTH;
            food.y = rand() % Tile::SCREEN_HEIGHT;
            while(foodInSnake()) {
                food.x = rand() % Tile::SCREEN_WIDTH;
                food.y = rand() % Tile::SCREEN_HEIGHT;
            }
            cout << "New food at (" << food.x << ", " << food.y << ")" << endl;
            screenTiles[food.x][food.y].setType(2);
        }

        if(!hitEdges && !hitSelf) {
            snakeBody.insert(snakeBody.begin(), newCoord);
            screenTiles[newCoord.x][newCoord.y].setType(1);
            if(deleteEnd) {
                Coord endCoord = snakeBody.at(snakeBody.size() - 1);
                screenTiles[endCoord.x][endCoord.y].setType(0);
                snakeBody.pop_back();
            }
        } else {
            gameOver = true;
            cout << "GAME OVER" << endl;
        }
        oldTime = high_resolution_clock::now();
    }

}

void Map::reset() {
    oldTime = high_resolution_clock::now();
    for(int i = 0; i < Tile::SCREEN_WIDTH; i++) {
        for(int j = 0; j < Tile::SCREEN_HEIGHT; j++) {
            screenTiles[i][j] = Tile(i, j);
        }
    }
    snakeBody.clear();
    snakeBody.push_back(head);

    head.x = Tile::SCREEN_WIDTH/2 + Tile::SCREEN_WIDTH/4;
    head.y = Tile::SCREEN_HEIGHT/2 - 1;
    food.x = Tile::SCREEN_WIDTH/2 - Tile::SCREEN_WIDTH/4;
    food.y = Tile::SCREEN_HEIGHT/2 - 1;
    screenTiles[head.x][head.y].setType(1);
    screenTiles[food.x][food.y].setType(2);
    gameOver = false;
    pastDirection = LEFT;
    direction = LEFT;
}

void Map::draw(RenderTarget& window) {
    for(int i = 0; i < Tile::SCREEN_WIDTH; i++) {
        for(int j = 0; j < Tile::SCREEN_HEIGHT; j++) {
            screenTiles[i][j].draw(window);
        }
    }
}

void Map::setDirection(int d) {
    direction = d;
}

int Map::getDirection() const {
    return pastDirection;
}

bool Map::foodInSnake() const {
    bool inSnake = false;
    for(int i = 0; i < snakeBody.size(); i++) {
        if(food.equals(snakeBody.at(i))) {
            inSnake = true;
            break;
        }
    }
    return inSnake;
}

unsigned int Map::getSnakeSize() const {
    return snakeBody.size();
}

#endif