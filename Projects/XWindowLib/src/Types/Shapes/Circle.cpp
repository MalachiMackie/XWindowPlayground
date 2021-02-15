#include "Circle.h"

#include <X11/Xlib.h>

namespace XWindowLib
{
    void Circle::Draw()
    {
        if (m_display && m_window)
        {
            if (m_fill)
                XFillArc(m_display.get(), *m_window, m_graphicsContext, m_position.x, m_position.y, m_dimensions.width, m_dimensions.height, 0, 360 * 64);
            else
                XDrawArc(m_display.get(), *m_window, m_graphicsContext, m_position.x, m_position.y, m_dimensions.width, m_dimensions.height, 0, 360 * 64);
        }
        Drawable::Draw();
    }

    Circle::Circle(Position position, Dimensions dimensions)
    {
        SetPosition(position);
        SetDimensions(dimensions);
    }
}