#include <X11/Xlib.h>
#include "Circle.h"

namespace XWindowPlayground
{
    void Circle::Draw()
    {
        if (m_display && m_window)
        {
            if (m_fill)
                XFillArc(m_display, *m_window, m_graphicsContext, m_x, m_y, m_width, m_height, 0, 360 * 64);
            else
                XDrawArc(m_display, *m_window, m_graphicsContext, m_x, m_y, m_width, m_height, 0, 360 * 64);
        }
    }
}