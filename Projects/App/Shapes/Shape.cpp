#include "Shape.h"

namespace XWindowPlayground
{
    void Shape::InitShape(Display* display, Window* window)
    {
        XColor xcolor;
        xcolor.blue = 0;
        xcolor.green = 0;
        xcolor.red = 65000;
        xcolor.flags = DoBlue | DoGreen | DoRed;
        Colormap map = XDefaultColormap(display, 0);
        XAllocColor(display, map, &xcolor);

        m_graphicsContext = XCreateGC(display, *window, 0, 0);
        XSetForeground(display, m_graphicsContext, xcolor.pixel);
    }
}