#include <X11/Xlib.h>
#include "Square.h"

namespace XWindowPlayground
{
    void Square::Draw()
    {
        if (m_display && m_window) {
            if (m_fill)
                XFillRectangle(m_display, *m_window, m_graphicsContext, m_x, m_y, m_width, m_height);
            else
                XDrawRectangle(m_display, *m_window, m_graphicsContext, m_x, m_y, m_width, m_height);
        }
    }
}