#ifndef COORD_HPP
#define COORD_HPP

struct Coord {
    Coord(const int X, const int Y) {
        x = X;
        y = Y;
    }

    bool equals(const Coord &OTHER) const {
        return x == OTHER.x && y == OTHER.y;
    }

    int x;
    int y;
};

#endif