#include <X11/Xlib.h>
#include "Circle.h"

namespace XWindowPlayground
{
    void Circle::Draw(Display* display, Window window) const
    {
        if (display && window)
        {
            XDrawArc(display, window, m_graphicsContext, m_x, m_y, m_width, m_height, 0, 360 * 64);
        }
    }
}