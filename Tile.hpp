#ifndef TILE_HPP
#define TILE_HPP

#include <SFML/Graphics.hpp>
using namespace sf;

class Tile {
    public:
        Tile();
        Tile(const int X, const int Y);
        void setType(const unsigned int TYPE);
        void draw(RenderTarget& window);

        static const int TILE_SIZE = 32;
        static const int SCREEN_WIDTH = 25;
        static const int SCREEN_HEIGHT = 25;
    private: 
        RectangleShape square;
        unsigned int type = 0; // 0 nothing, 1 green (snake), 2 red (food)
};

Tile::Tile() {}

Tile::Tile(const int X, const int Y) {
    square.setSize(Vector2f(TILE_SIZE * 0.8, TILE_SIZE * 0.8));
    square.setPosition(X * TILE_SIZE + TILE_SIZE * 0.1, Y * TILE_SIZE + TILE_SIZE * 0.1);
    square.setFillColor(Color::Black);
}

void Tile::setType(const unsigned int TYPE) {
    type = TYPE;
}

void Tile::draw(RenderTarget& window) {
    if(type == 1) {
        square.setFillColor(Color::Green);
        window.draw(square);
    } else if(type == 2) {
        square.setFillColor(Color::Red);
        window.draw(square);
    }
}


#endif