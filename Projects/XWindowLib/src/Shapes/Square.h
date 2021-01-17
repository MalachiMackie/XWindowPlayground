#ifndef SQUARE_H
#define SQUARE_H

#include <X11/Xlib.h>
#include "Shape.h"

namespace XWindowPlayground
{
    class Square : public Shape
    {
    private:
        int m_width;
        int m_height;
        int m_x;
        int m_y;

    public:
        Square(int x, int y, int width, int height)
            : m_width{width},
            m_height{height},
            m_x{x},
            m_y{y}
        {};
        Square(){};
        virtual ~Square() override {};

        virtual void Draw() override;
        void Set(int x, int y, int width, int height);
    };
}

#endif