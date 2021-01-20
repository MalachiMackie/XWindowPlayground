#ifndef DRAWABLE_H
#define DRAWABLE_H

#include <X11/Xlib.h>
#include <memory>

namespace XWindowLib
{
    class Drawable
    {
    protected:
        std::shared_ptr<Display> m_display;
        std::shared_ptr<Window> m_window;

        bool m_isInitialized = false;

    public:
        virtual void Draw() = 0;
        virtual void Init(std::shared_ptr<Display> display, std::shared_ptr<Window> window);
    };
}

#endif