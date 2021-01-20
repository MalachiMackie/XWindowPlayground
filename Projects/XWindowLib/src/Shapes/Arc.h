#ifndef ARC_H
#define ARC_H

#include "Shapes/Shape.h"

namespace XWindowLib
{
    class Arc : public Shape
    {
        int m_startDegrees;
        int m_degrees;
        int m_x;
        int m_y;
        int m_width;
        int m_height;

    public:
        Arc(int x, int y, int width, int height, int startDegrees, int degrees)
            : m_x{x}, m_y{y}, m_width{width}, m_height{height}, m_startDegrees{startDegrees}, m_degrees{degrees}
            {};

        virtual void Draw() override;
    };
}

#endif