#include <X11/Xlib.h>
#include "Square.h"

namespace XWindowPlayground
{
    void Square::Draw()
    {
        if (m_display && m_window) {
            if (m_fill)
                XFillRectangle(m_display.get(), *m_window, m_graphicsContext, m_x, m_y, m_width, m_height);
            else
                XDrawRectangle(m_display.get(), *m_window, m_graphicsContext, m_x, m_y, m_width, m_height);
        }
    }

    void Square::Set(int x, int y, int width, int height)
    {
        if (m_display
            && (m_x != x || m_y != y || m_width != width || m_height != height))
        {
            XClearArea(m_display.get(), *m_window, m_x, m_y, m_width, m_height, false);
        }
        m_x = x;
        m_y = y;
        m_width = width;
        m_height = height;
    }
}