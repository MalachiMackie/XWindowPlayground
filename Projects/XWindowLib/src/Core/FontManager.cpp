#include "FontManager.h"

namespace XWindowLib
{
    FontManager FontManager::s_fontManager;

    FontManager& FontManager::GetFontManager(std::shared_ptr<Display> display)
    {
        if (!s_fontManager.m_isInitialized)
        {
            s_fontManager = FontManager{display};
        }
        return s_fontManager;
    }

    Font FontManager::LoadFont(const std::string& name)
    {
        Font font = m_fontMap[name];
        if (!font)
        {
            font = XLoadFont(m_display.get(), name.c_str());
            m_fontMap[name] = font;
        }
        return font;
    }

    void FontManager::SetFont(const GC& graphicsContext, const std::string& fontName)
    {
        Font font = LoadFont(fontName);
        XSetFont(m_display.get(), graphicsContext, font);
    }

    XFontStruct* FontManager::GetFont(const std::string& name)
    {
        Font font = LoadFont(name);

        return XQueryFont(m_display.get(), font);
    }

    int FontManager::GetTextWidth(const std::string& font, const std::string& text)
    {
        return XTextWidth(GetFont(font), text.c_str(), text.length());
    }

    int FontManager::GetFontHeight(const std::string& font)
    {
        const auto& fontStruct = GetFont(font);
        return fontStruct->max_bounds.ascent + fontStruct->max_bounds.descent;
    }

    void FontManager::FreeFonts()
    {
        for (auto &&font : m_fontMap)
        {
            XFontStruct* fontStruct = XQueryFont(m_display.get(), font.second);
            if (fontStruct)
            {
                XFreeFont(m_display.get(), fontStruct);
            }
        }
        m_fontMap.clear();
    }
}