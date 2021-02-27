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

    struct Margin
    {
        int left = 0;
        int top = 0;
        int right = 0;
        int bottom = 0;

        Margin() {};
        Margin(int margin)
        {
            left = margin;
            top = margin;
            right = margin;
            bottom = margin;
        }
        Margin(int horizontal, int vertical)
        {
            left = horizontal;
            right = horizontal;
            top = vertical;
            bottom = vertical;
        }
        Margin(int left, int top, int right, int bottom)
        {
            Margin::left = left;
            Margin::top = top;
            Margin::right = right;
            Margin::bottom =  bottom;
        }

        bool operator==(Margin other)
        {
            return left == other.left
                && top == other.top
                && right == other.right
                && bottom == other.bottom;
        }

        bool operator!=(Margin other)
        {
            return !(*this == other);
        }
    };
}

#endif