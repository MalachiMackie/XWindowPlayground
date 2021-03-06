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
        Drawable::Draw();
    }

    void Square::Set(Position position, Dimensions dimensions)
    {
        m_position = position;
        m_dimensions = dimensions;
    }

    void Square::Set(int x, int y, int width, int height)
    {
        Set({x, y}, {width, height});
    }

    void Square::SetBorderWidth(int borderWidth)
    {
        if (m_lineWidth == borderWidth)
            return;
            
        m_lineWidth = borderWidth;
        if (m_isInitialized)
        {
            XGCValues values;
            values.line_width = borderWidth;
            XChangeGC(m_display.get(), m_graphicsContext, GCLineWidth, &values);
        }
    }
}