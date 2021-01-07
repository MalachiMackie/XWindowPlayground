#include "Manager.h"
#include <exception>

#define NIL (0)

namespace XWindowPlayground
{
    void Manager::Initialize()
    {
        m_display = XOpenDisplay(NIL);
        if (!m_display) throw std::bad_exception{};

        m_colorBlack = BlackPixel(m_display, DefaultScreen(m_display));
        m_colorWhite = WhitePixel(m_display, DefaultScreen(m_display));

        m_window = new Window{XCreateSimpleWindow(m_display, DefaultRootWindow(m_display), 0, 0, 200, 200, 0, m_colorBlack, m_colorBlack)};

        // tell XWindows server which events we want.
        // Structure events include window structural changes as well as mapping changes
        XSelectInput(m_display, *m_window, StructureNotifyMask);
        m_wmDeleteMessage = XInternAtom(m_display, "WM_DELETE_WINDOW", NIL);
        XSetWMProtocols(m_display, *m_window, &m_wmDeleteMessage, 1);

        // map window to display
        XMapWindow(m_display, *m_window);

        XSizeHints* sizeHints = XAllocSizeHints();
        sizeHints->flags = PMinSize;
        sizeHints->min_width = 200;
        sizeHints->min_height = 200;

        XSetWMNormalHints(m_display, *m_window, sizeHints);
    }

    int Manager::EventLoop()
    {
        XEvent e;
        XNextEvent(m_display, &e);
        if (e.type == MapNotify)
        {
            for (auto &&shape : m_shapes)
            {
                shape->Draw(m_display, *m_window);
            }

            // send request to server
            XFlush(m_display);
        }
        else if (e.type == ClientMessage && e.xclient.data.l[0] == m_wmDeleteMessage)
        {
            return 1;
        }
        else if (e.type == ConfigureNotify)
        {
            for (auto &&shape : m_shapes)
            {
                shape->Draw(m_display, *m_window);
            }


            XFlush(m_display);
        }

        return 0;
    }

    void Manager::AddShape(Shape* shape)
    {
        shape->InitShape(m_display, m_window);
        m_shapes.push_back(shape);
    }

    Manager::~Manager()
    {
        delete m_window;
        for (auto shape : m_shapes)
        {
            delete shape;
        }
        
    }
}