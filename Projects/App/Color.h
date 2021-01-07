#ifndef COLOR_H
#define COLOR_H

#include <X11/Xlib.h>

namespace XWindowPlayground
{
    struct Color
    {
    private:
        int m_r = 0;
        int m_g = 0;
        int m_b = 0;

        bool m_set = false;

    public:

        void Set(int r = 0, int g = 0, int b = 0)
        {
            m_r = r;
            m_g = g;
            m_b = b;
            m_set = true;
        } 

        XColor ToXColor()
        {
            XColor color;
            color.red = m_r;
            color.green = m_g;
            color.blue = m_b;
            color.flags = DoRed | DoGreen | DoBlue;
            return color;
        }

        bool IsDefault() { return !m_set; }
    };
}

#endif