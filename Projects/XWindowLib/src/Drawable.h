#ifndef DRAWABLE_H
#define DRAWABLE_H

#include <X11/Xlib.h>

namespace XWindowPlayground
{
    class Drawable
    {
    protected:
        Display* m_display;
        Window* m_window;

        bool m_isInitialized = false;

    public:
        virtual void Draw() = 0;
        virtual void Init(Display* display, Window* window);
    };
}

#endif