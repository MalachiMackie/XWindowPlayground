#include "Manager.h"
#include <exception>
#include <iostream>
#include <sstream>
#include <random>
#include <string>

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
            drawable.second->Draw();
        }
        XFlush(m_display.get());
    }

    int Manager::EventLoop()
    {
        XEvent e;
        XNextEvent(m_display.get(), &e);

        if (e.type == MapNotify || e.type == ConfigureNotify)
        {
            Draw();
        }
        else if (e.type == ClientMessage && e.xclient.data.l[0] == m_wmDeleteMessage)
        {
            FontManager::GetFontManager(m_display).FreeFonts();
            return 1;
        }
        else if (e.type == MotionNotify)
        {
            for (auto &&drawable : m_drawables)
            {
                Hoverable* hoverable = dynamic_cast<Hoverable*>(drawable.second.get());
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
                Clickable* clickable = dynamic_cast<Clickable*>(drawable.second.get());
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
                Clickable* clickable = dynamic_cast<Clickable*>(drawable.second.get());
                if (clickable)
                {
                    clickable->DoClickRelease(e.xbutton.button);
                }
            }
        }

        if (m_changed)
        {
            XClearWindow(m_display.get(), *m_window);
            Draw();
            m_changed = false;
        }

        return 0;
    }

    unsigned int random_char() {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, 255);
        return dis(gen);
    }

    std::string generate_hex(const unsigned int len) {
        std::stringstream ss;
        for (auto i = 0; i < len; i++) {
            const auto rc = random_char();
            std::stringstream hexstream;
            hexstream << std::hex << rc;
            auto hex = hexstream.str();
            ss << (hex.length() < 2 ? '0' + hex : hex);
        }
        return ss.str();
    }

    void Manager::AddDrawable(std::unique_ptr<Drawable>&& drawable)
    {
        AddDrawable(std::move(drawable), generate_hex(10));
    }

    void Manager::AddDrawable(std::unique_ptr<Drawable>&& drawable, const std::string& name)
    {
        drawable->SetOnDraw([this](){
            m_changed = true;
        });
        drawable->Init(m_display, m_window);
        const auto& existing = m_drawables[name];
        if (existing)
        {
            throw "drawable with that name already exists";
        }
        m_drawables[name] = std::move(drawable);
    }

    const std::unique_ptr<Drawable>& Manager::GetDrawable(const std::string& name)
    {
        const auto& existing = m_drawables[name];
        if (!existing)
        {
            throw "drawable does not exist";
        }
        return existing;
    }

    Manager::~Manager() {}
}