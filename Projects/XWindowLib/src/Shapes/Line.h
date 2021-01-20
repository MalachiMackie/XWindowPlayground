#ifndef LINE_H
#define LINE_H

#include "Shapes/Shape.h"
#include "Pairs.h"

namespace XWindowLib
{
    class Line : public Shape
    {
        Position m_pos1;
        Position m_pos2;

    public:
        Line(int x1, int y1, int x2, int y2)
            : Line{Position{x1, y1}, Position{x2, y2}}
            {};
        Line(std::pair<int, int> pos1, std::pair<int, int> pos2)
            : m_pos1{pos1}, m_pos2{pos2}
            {};

        Line(Position pos1, Position pos2)
            : m_pos1{pos1}, m_pos2{pos2}
            {};

        virtual void Draw() override;
    };
}

#endif