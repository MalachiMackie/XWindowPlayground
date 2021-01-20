#include "Manager.h"
#include <exception>
#include <iostream>

#include "Types/Widgets/Button.h"

#define NIL (0)

namespace XWindowLib
{
    void Manager::Initialize()
    {
        m_display = std::shared_ptr<Display>(XOpenDisplay(NIL));

        if (!m_display) throw std::bad_exception{};

        m_colorBlack = BlackPixel(m_display.get(), DefaultScreen(m_display.get()));
        m_colorWhite = WhitePixel(m_display.get(), DefaultScreen(m_display.get()));

        m_window = std::make_shared<Window>(XCreateSimpleWindow(m_display.get(), DefaultRootWindow(m_display.get()), 0, 0, m_width, m_height, 0, m_colorWhite, m_colorWhite));

        // tell XWindows server which events we want.
        // Structure events include window structural changes as well as mapping changes
        XSelectInput(m_display.get(), *m_window, StructureNotifyMask | PointerMotionMask | ButtonPressMask | ButtonReleaseMask);
        m_wmDeleteMessage = XInternAtom(m_display.get(), "WM_DELETE_WINDOW", NIL);
        XSetWMProtocols(m_display.get(), *m_window, &m_wmDeleteMessage, 1);

        // map window to display
        XMapWindow(m_display.get(), *m_window);

        XSizeHints* sizeHints = XAllocSizeHints();
        sizeHints->flags = PMinSize;
        sizeHints->min_width = m_minWidth;
        sizeHints->min_height = m_minHeight;

        XSetWMNormalHints(m_display.get(), *m_window, sizeHints);
    }

    void Manager::Draw()
    {
        for (auto &&drawable : m_drawables)
        {
            drawable->Draw();
        }
        XFlush(m_display.get());
    }

    int Manager::EventLoop()
    {
        Draw(); // TODO: only do this when XClearArea is called
        XEvent e;
        XNextEvent(m_display.get(), &e);
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
                Hoverable* hoverable = dynamic_cast<Hoverable*>(drawable.get());
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
                Clickable* clickable = dynamic_cast<Clickable*>(drawable.get());
                if (clickable)
                {
                    clickable->DoClick(e.xbutton.button);
                }
            }
        }
        else if (e.type == ButtonRelease)
        {
            for(auto&& drawable : m_drawables)
            {
                Clickable* clickable = dynamic_cast<Clickable*>(drawable.get());
                if (clickable)
                {
                    clickable->DoClickRelease(e.xbutton.button);
                }
            }
        }

        return 0;
    }

    void Manager::AddDrawable(std::unique_ptr<Drawable>&& drawable)
    {
        drawable->Init(m_display, m_window);
        m_drawables.push_back(std::move(drawable));
    }

    Manager::~Manager() {}
}