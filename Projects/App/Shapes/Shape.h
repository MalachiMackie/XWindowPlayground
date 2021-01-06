#ifndef SHAPE_H
#define SHAPE_H

#include <X11/Xlib.h>

namespace XWindowPlayground {
    class Shape
    {
    protected:
        GC m_graphicsContext;
        int m_borderColor;

    public:
        virtual ~Shape() {};

        virtual void Draw(Display* dpy, Window window) const = 0;

        virtual void InitShape(Display* display, Window* window);

        void SetBorderColor(int color) { m_borderColor = color; }

        const GC& GetGC() const { return m_graphicsContext; }
    };
}

#endif