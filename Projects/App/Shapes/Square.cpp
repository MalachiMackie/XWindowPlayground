#include <X11/Xlib.h>
#include "Square.h"

namespace XWindowPlayground
{
    void Square::Draw(Display* dpy, Window window) const
    {
        if (dpy && window) {
            if (m_fill)
                XFillRectangle(dpy, window, m_graphicsContext, m_x, m_y, m_width, m_height);
            else
                XDrawRectangle(dpy, window, m_graphicsContext, m_x, m_y, m_width, m_height);
        }
    }
}