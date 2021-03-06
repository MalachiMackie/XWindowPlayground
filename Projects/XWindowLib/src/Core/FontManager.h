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
        static FontManager s_fontManager;

    public:
        static FontManager& GetFontManager(std::shared_ptr<Display> display);

    private:
        std::shared_ptr<Display> m_display;
        bool m_isInitialized = false;

        Font LoadFont(const std::string& name);
        std::map<std::string, Font> m_fontMap;

    private:

        FontManager(std::shared_ptr<Display> display)
            : m_display{display}, m_isInitialized{true}
            {};
        FontManager()
            : m_isInitialized {false}
            {}


        FontManager(const FontManager&) = delete;
        FontManager& operator= (const FontManager&) = default;
        

    public:

        XFontStruct* GetFont(const std::string& name);

        void SetFont(const GC& graphicsContext, const std::string& fontName);

        int GetTextWidth(const std::string& name, const std::string& text);
        int GetFontHeight(const std::string& name);

        void FreeFonts();

    };
}

#endif