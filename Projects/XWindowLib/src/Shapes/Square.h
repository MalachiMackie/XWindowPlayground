#ifndef SQUARE_H
#define SQUARE_H

#include <X11/Xlib.h>
#include "Shape.h"
#include "Pairs.h"

namespace XWindowLib
{
    class Square : public Shape
    {
    private:
        Dimensions m_dimensions;
        Position m_position;

    public:
        Square(int x, int y, int width, int height)
            : Square(Position{x, y}, Dimensions{width, height})
        {};
        Square(Position position, Dimensions dimensions)
            : m_position{position}, m_dimensions{dimensions}
            {};
        Square(){};
        virtual ~Square() override {};

        virtual void Draw() override;
        void Set(int x, int y, int width, int height);
        void Set(Position pos, Dimensions dimensions);
    };
}

#endif