#ifndef PAIR_H
#define PAIR_H

#include <utility>

namespace XWindowLib
{
    struct Dimensions
    {
        int width = 0;
        int height = 0;

        Dimensions(int width, int height)
        {
            Dimensions::width = width;
            Dimensions::height = height;
        }
        Dimensions(std::pair<int, int> pair)
        {
            width = pair.first;
            height = pair.second;
        }
        Dimensions(){};

        bool operator==(Dimensions other)
        {
            return width == other.width && height == other.height;
        }

        bool operator!=(Dimensions other)
        {
            return !(*this == other);
        }
    };

    struct Position
    {
        int x = 0;
        int y = 0;

        Position(int x, int y)
        {
            Position::x = x;
            Position::y = y;
        }
        Position(std::pair<int, int> pair)
        {
            Position::x = pair.first;
            Position::y = pair.second;
        }
        Position(){};

        bool operator==(Position other)
        {
            return x == other.x && y == other.y;
        }

        bool operator!=(Position other)
        {
            return !(*this == other);
        }
    };
    
}

#endif