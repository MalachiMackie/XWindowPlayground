#ifndef MANAGER_H
#define MANAGER_H

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <unistd.h>
#include <vector>
#include "Shapes/Shape.h"
#include "Drawable.h"

namespace XWindowPlayground
{
    class Manager
    {
    private:
        Display* m_display;
        Window* m_window;

        int m_colorWhite, m_colorBlack;
        int m_width, m_height;
        int m_minWidth, m_minHeight;
        bool m_changed = false;

        Atom m_wmDeleteMessage;

        std::vector<Drawable*> m_drawables;

    private:
        void Draw();

    public:
        Manager(int width = 200, int height = 200, int minWidth = 200, int minHeight = 200)
            : m_width{width}, m_height{height}, m_minWidth{minWidth}, m_minHeight{minHeight}
        {}

        int EventLoop();
        void Initialize();

        void AddDrawable(Drawable* drawable);

        ~Manager();
    };
}

#endif
