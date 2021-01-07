#include "Shape.h"

namespace XWindowPlayground
{
    void Shape::InitShape(Display* display, Window* window)
    {
        m_graphicsContext = XCreateGC(display, *window, 0, 0);
        Colormap map = XDefaultColormap(display, 0);
        if (!m_color.IsDefault())
        {
            XColor xColor = m_color.ToXColor();
            XAllocColor(display, map, &xColor);
            XSetForeground(display, m_graphicsContext, xColor.pixel);
        }
            
    }
}