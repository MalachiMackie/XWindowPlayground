#include "Arc.h"

namespace XWindowLib
{
    void Arc::Draw()
    {
        if (m_display && m_window)
        {
            if (m_fill)
                XFillArc(m_display.get(), *m_window, m_graphicsContext, m_x, m_y, m_width, m_height, 0 - m_startDegrees * 64, 0 - m_degrees * 64);
            else
                XDrawArc(m_display.get(), *m_window, m_graphicsContext, m_x, m_y, m_width, m_height, 0 - m_startDegrees * 64, 0 - m_degrees * 64);
        }
    }
}