#include <SFML/Graphics.hpp>
using namespace sf;
#include "Map.hpp"

#include <iostream>
using namespace std;

int main() {

    // Load things here
    Map map = Map();

    static const int TILE_SIZE = Tile::TILE_SIZE;
    static const int SCREEN_WIDTH = Tile::SCREEN_WIDTH;
    static const int SCREEN_HEIGHT = Tile::SCREEN_HEIGHT;
    RenderWindow window( VideoMode(SCREEN_WIDTH * TILE_SIZE, SCREEN_HEIGHT * TILE_SIZE), "Snake" );

    // Window loop
    while(window.isOpen()) {
        window.clear();
        //Draw stuff here

        map.update();
        map.draw(window);

        window.display();

        Event event;
        while( window.pollEvent(event) ) {
            // if event type corresponds to pressing window X
            if(event.type == Event::Closed) {
                // tell the window to close
                window.close();
            }
            // check addition event types to handle additional events

            if (event.type == Event::EventType::KeyPressed){
                if(event.key.code == Keyboard::Left && (map.getDirection() != map.RIGHT || map.getSnakeSize() == 1)) map.setDirection(map.LEFT);
                if(event.key.code == Keyboard::Right && (map.getDirection() != map.LEFT || map.getSnakeSize() == 1)) map.setDirection(map.RIGHT);
                if(event.key.code == Keyboard::Up && (map.getDirection() != map.DOWN || map.getSnakeSize() == 1)) map.setDirection(map.UP);
                if(event.key.code == Keyboard::Down && (map.getDirection() != map.UP || map.getSnakeSize() == 1)) map.setDirection(map.DOWN);
                if(event.key.code == Keyboard::R) {
                    map.reset();
                    cout << "Reset!" << endl;
                }
            }
        }
    }

    return 0;
}