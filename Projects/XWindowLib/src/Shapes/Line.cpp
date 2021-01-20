#include "Line.h"

namespace XWindowLib
{
    void Line::Draw()
    {
        if (m_display && m_window)
        {
            XDrawLine(m_display.get(), *m_window, m_graphicsContext, m_pos1.x, m_pos1.y, m_pos2.x, m_pos2.y);
        }
    }
}