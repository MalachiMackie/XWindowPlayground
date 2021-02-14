#include "Square.h"

#include <X11/Xlib.h>

namespace XWindowLib
{

    Square::Square(Position position, Dimensions dimensions)
    {
        SetPosition(position);
        SetDimensions(dimensions);
    }

    void Square::Draw()
    {
        if (m_display && m_window) {
            if (m_fill)
                XFillRectangle(m_display.get(), *m_window, m_graphicsContext, m_position.x, m_position.y, m_dimensions.width, m_dimensions.height);
            else
                XDrawRectangle(m_display.get(), *m_window, m_graphicsContext, m_position.x, m_position.y, m_dimensions.width, m_dimensions.height);
        }
    }

    void Square::Set(Position position, Dimensions dimensions)
    {
        if (m_display && (m_position != position || m_dimensions != dimensions))
        {
            XClearArea(m_display.get(), *m_window, m_position.x, m_position.y, m_dimensions.width, m_dimensions.height, false);
        }
        m_position = position;
        m_dimensions = dimensions;
    }

    void Square::Set(int x, int y, int width, int height)
    {
        Set({x, y}, {width, height});
    }
}