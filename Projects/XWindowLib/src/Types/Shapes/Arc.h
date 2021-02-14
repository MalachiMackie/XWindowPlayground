#ifndef ARC_H
#define ARC_H

#include "Types/Shapes/Shape.h"

namespace XWindowLib
{
    class Arc : public Shape
    {
        int m_startDegrees;
        int m_degrees;

    public:
        Arc(Position position, Dimensions dimensions, int startDegrees, int degrees);

        virtual void Draw() override;
    };
}

#endif