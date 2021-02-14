#ifndef MANAGER_H
#define MANAGER_H

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <unistd.h>
#include <vector>
#include <memory>
#include <map>
#include <string>
#include "Types/Shapes/Shape.h"
#include "Types/Drawable.h"

namespace XWindowLib
{
    class Manager
    {
    private:
        std::shared_ptr<Display> m_display;
        std::shared_ptr<Window> m_window;

        int m_colorWhite, m_colorBlack;
        int m_width, m_height;
        int m_minWidth, m_minHeight;
        bool m_changed = false;

        Atom m_wmDeleteMessage;

        std::map<std::string, std::unique_ptr<Drawable>> m_drawables;

    private:
        void Draw();

    public:
        Manager(int width = 200, int height = 200, int minWidth = 200, int minHeight = 200)
            : m_width{width}, m_height{height}, m_minWidth{minWidth}, m_minHeight{minHeight}
        {}

        int EventLoop();
        void Initialize();

        void AddDrawable(std::unique_ptr<Drawable>&& drawable);
        void AddDrawable(std::unique_ptr<Drawable>&& drawable, const std::string& name);

        const std::unique_ptr<Drawable>& GetDrawable(const std::string& name);

        ~Manager();
    };
}

#endif
