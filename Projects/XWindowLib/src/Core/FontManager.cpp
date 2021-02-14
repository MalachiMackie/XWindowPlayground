#include "FontManager.h"

namespace XWindowLib
{
    std::shared_ptr<FontManager> FontManager::s_fontManager;

    std::shared_ptr<FontManager> FontManager::GetFontManager(std::shared_ptr<Display> display)
    {
        if (!s_fontManager)
        {
            s_fontManager = std::make_shared<FontManager>(display);
        }
        return FontManager::s_fontManager;
    }

    XFontStruct* FontManager::GetFont(std::string name)
    {
        auto* font = m_fontMap[name];
        
        if (!font)
        {
            m_fontMap[name] = XLoadQueryFont(m_display.get(), name.c_str());
            return m_fontMap[name];
        }
        else
        {
            return font;
        }
    }

    int FontManager::GetTextWidth(std::string font, std::string text)
    {
        return XTextWidth(GetFont(font), text.c_str(), text.length());
    }

    int FontManager::GetFontHeight(std::string font)
    {
        const auto& fontStruct = GetFont(font);
        return fontStruct->max_bounds.ascent + fontStruct->max_bounds.descent;
    }

    FontManager::~FontManager()
    {
        for (auto &&font : m_fontMap)
        {
            XFreeFont(m_display.get(), font.second);
        }
        m_fontMap.clear();
    }
}