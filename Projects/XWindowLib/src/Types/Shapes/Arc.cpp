#include "Arc.h"

namespace XWindowLib
{
    void Arc::Draw()
    {
        if (m_display && m_window)
        {
            if (m_fill)
                XFillArc(m_display.get(), *m_window, m_graphicsContext, m_position.x, m_position.y, m_dimensions.width, m_dimensions.height, 0 - m_startDegrees * 64, 0 - m_degrees * 64);
            else
                XDrawArc(m_display.get(), *m_window, m_graphicsContext, m_position.x, m_position.y, m_dimensions.width, m_dimensions.height, 0 - m_startDegrees * 64, 0 - m_degrees * 64);
        }
        Drawable::Draw();
    }

    Arc::Arc(Position position, Dimensions dimensions, int startDegrees, int degrees)
            : m_startDegrees{startDegrees}, m_degrees{degrees}
    {
        SetPosition(position);
        SetDimensions(dimensions);
    };
}