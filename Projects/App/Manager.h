#ifndef MANAGER_H
#define MANAGER_H

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <unistd.h>
#include <vector>
#include "Shapes/Shape.h"

namespace XWindowPlayground
{
    class Manager
    {
    private:
        Display* m_display;
        Window* m_window;

        int m_colorWhite;
        int m_colorBlack;

        Atom m_wmDeleteMessage;

        std::vector<Shape*> m_shapes;

    public:
        int EventLoop();
        void Initialize();

        void AddShape(Shape* shape);

        ~Manager();
    };
}

#endif
