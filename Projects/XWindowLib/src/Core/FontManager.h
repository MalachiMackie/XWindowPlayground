#ifndef FONT_MANAGER_H
#define FONT_MANAGER_H

#include <memory>
#include <X11/Xlib.h>
#include <map>

namespace XWindowLib
{
    class FontManager
    {
    private:
        static std::shared_ptr<FontManager> s_fontManager;

    public:
        static std::shared_ptr<FontManager> GetFontManager(std::shared_ptr<Display> display);

    private:
        std::shared_ptr<Display> m_display;

        std::map<std::string, std::shared_ptr<XFontStruct>> m_fontMap;

    public:
        FontManager(std::shared_ptr<Display> display)
            : m_display{display}{};
        ~FontManager();

        std::shared_ptr<XFontStruct> GetFont(std::string name);

        int GetTextWidth(std::string name, std::string text);
        int GetFontHeight(std::string name);

    };
}

#endif