#ifndef COLOR_H
#define COLOR_H

#include <X11/Xlib.h>
#include <map>

namespace XWindowLib
{
    struct Color
    {
    private:
        int m_r = 0;
        int m_g = 0;
        int m_b = 0;

        bool m_set = false;

    public:

        Color() {};
        Color(int r, int g, int b)
        {
            Set(r, g, b);
        }

        void Set(int r = 0, int g = 0, int b = 0)
        {
            m_r = r;
            m_g = g;
            m_b = b;
            m_set = true;
        } 

        XColor ToXColor() const
        {
            XColor color;
            color.red = m_r;
            color.green = m_g;
            color.blue = m_b;
            color.flags = DoRed | DoGreen | DoBlue;
            return color;
        }

        bool IsDefault() const { return !m_set; }

        std::size_t Hash() const
        {
            int hash;
            std::hash<int> hasher;
            hash = hasher(m_r);
            hash ^= hasher(m_g) + 0x9e3779b9 + (hash << 6) + (hash >> 2);
            hash ^= hasher(m_b) + 0x9e3779b9 + (hash << 6) + (hash >> 2);
            return hash;
        }

        bool operator==(Color other)
        {
            return m_r == other.m_r
                && m_g == other.m_g
                && m_b == other.m_b
                && m_set == other.m_set;
        }

        bool operator!=(Color other)
        {
            return !(*this == other);
        }
    };
}

namespace std
{
    using namespace XWindowLib;

    template<> struct less<Color>
    {
        bool operator() (const Color& lhs, const Color& rhs)
        {
            return lhs.Hash() < rhs.Hash();
        }  
    };
}

#endif