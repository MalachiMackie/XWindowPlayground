#ifndef SHAPE_H
#define SHAPE_H

#include <X11/Xlib.h>
#include "../Color.h"

namespace XWindowPlayground {
    class Shape
    {
    protected:
        GC m_graphicsContext;
        Color m_color;

        bool m_fill;

    public:
        virtual ~Shape() {};

        virtual void Draw(Display* dpy, Window window) const = 0;

        virtual void InitShape(Display* display, Window* window);

        void SetColor(Color color) { m_color = color; }
        void Fill() { m_fill = true; }

        const GC& GetGC() const { return m_graphicsContext; }
    };
}

#endif