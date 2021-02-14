#ifndef CIRCLE_H
#define CIRCLE_H

#include <X11/Xlib.h>
#include "Types/Shapes/Shape.h"

namespace XWindowLib
{
    class Circle : public Shape
    {
    public:

        Circle(Position position, Dimensions dimensions);
        
        virtual ~Circle() override {};

        virtual void Draw() override;
    };
}

#endif