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

    std::shared_ptr<XFontStruct> FontManager::GetFont(std::string name)
    {
        auto fontIterator = m_fontMap.find(name);
        std::shared_ptr<XFontStruct> fontStruct;
        if (fontIterator == m_fontMap.end())
        {
            fontStruct = std::shared_ptr<XFontStruct>(XLoadQueryFont(m_display.get(), name.c_str()));
            m_fontMap[name] = fontStruct;
        }
        else
        {
            fontStruct = (*fontIterator).second;
        }
        return fontStruct;
    }

    int FontManager::GetTextWidth(std::string font, std::string text)
    {
        return XTextWidth(GetFont(font).get(), text.c_str(), text.length());
    }

    int FontManager::GetFontHeight(std::string font)
    {
        std::shared_ptr<XFontStruct> fontStruct = GetFont(font);
        return fontStruct->max_bounds.ascent + fontStruct->max_bounds.descent;
    }

    FontManager::~FontManager()
    {
        for (auto &&font : m_fontMap)
        {
            XFreeFont(m_display.get(), font.second.get());
        }
        m_fontMap.clear();
    }
}