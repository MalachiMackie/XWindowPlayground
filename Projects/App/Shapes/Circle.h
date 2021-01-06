#ifndef CIRCLE_H
#define CIRCLE_H

#include <X11/Xlib.h>
#include "Shape.h"

namespace XWindowPlayground
{
    class Circle : public Shape
    {
    private:
        int m_x;
        int m_y;
        int m_width;
        int m_height;

    public:

        Circle(int x, int y, int width, int height)
            : m_x{x},
            m_y{y},
            m_width{width},
            m_height{height}
            {};
        
        virtual ~Circle() override {};

        virtual void Draw(Display* display, Window window) const override;
    };
}

#endif