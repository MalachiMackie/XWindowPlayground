#ifndef SQUARE_H
#define SQUARE_H

#include <X11/Xlib.h>
#include "Types/Shapes/Shape.h"
#include "Utils/Pairs.h"

namespace XWindowLib
{
    class Square : public Shape
    {
    public:
        Square(Position position, Dimensions dimensions);
        Square(){};
        virtual ~Square() override {};

        virtual void Draw() override;
        void Set(int x, int y, int width, int height);
        void Set(Position pos, Dimensions dimensions);
        void SetBorderWidth(int borderWidth);
        int GetBorderWidth() { return m_lineWidth; }
    };
}

#endif