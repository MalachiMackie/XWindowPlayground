#include "Manager.h"
#include <exception>
#include <iostream>

#include "Widgets/Button.h"

#define NIL (0)

namespace XWindowPlayground
{
    void Manager::Initialize()
    {
        m_display = XOpenDisplay(NIL);
        if (!m_display) throw std::bad_exception{};

        m_colorBlack = BlackPixel(m_display, DefaultScreen(m_display));
        m_colorWhite = WhitePixel(m_display, DefaultScreen(m_display));

        m_window = new Window{XCreateSimpleWindow(m_display, DefaultRootWindow(m_display), 0, 0, m_width, m_height, 0, m_colorWhite, m_colorWhite)};

        // tell XWindows server which events we want.
        // Structure events include window structural changes as well as mapping changes
        XSelectInput(m_display, *m_window, StructureNotifyMask | PointerMotionMask | ButtonPressMask);
        m_wmDeleteMessage = XInternAtom(m_display, "WM_DELETE_WINDOW", NIL);
        XSetWMProtocols(m_display, *m_window, &m_wmDeleteMessage, 1);

        // map window to display
        XMapWindow(m_display, *m_window);

        XSizeHints* sizeHints = XAllocSizeHints();
        sizeHints->flags = PMinSize;
        sizeHints->min_width = m_minWidth;
        sizeHints->min_height = m_minHeight;

        XSetWMNormalHints(m_display, *m_window, sizeHints);
    }

    void Manager::Draw()
    {
        for (auto &&drawable : m_drawables)
        {
            drawable->Draw();
        }
        XFlush(m_display);
    }

    int Manager::EventLoop()
    {
        XEvent e;
        XNextEvent(m_display, &e);
        if (e.type == MapNotify || e.type == ConfigureNotify)
        {
            Draw();
        }
        else if (e.type == ClientMessage && e.xclient.data.l[0] == m_wmDeleteMessage)
        {
            return 1;
        }
        else if (e.type == MotionNotify)
        {
            for (auto &&drawable : m_drawables)
            {
                Hoverable* hoverable = dynamic_cast<Hoverable*>(drawable);
                if (hoverable)
                {
                    hoverable->CheckHovering(e.xmotion.x, e.xmotion.y);
                }
            }
        }
        else if (e.type == ButtonPress)
        {
            for (auto &&drawable : m_drawables)
            {
                Clickable* clickable = dynamic_cast<Clickable*>(drawable);
                if (clickable)
                {
                    clickable->DoClick(e.xbutton.button);
                }
            }
        }

        return 0;
    }

    void Manager::AddDrawable(Drawable* drawable)
    {
        drawable->Init(m_display, m_window);
        m_drawables.push_back(drawable);
    }

    Manager::~Manager()
    {
        delete m_window;
        for (auto drawable : m_drawables)
        {
            delete drawable;
        }
        
    }
}