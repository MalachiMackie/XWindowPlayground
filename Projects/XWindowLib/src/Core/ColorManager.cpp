#include "ColorManager.h"

namespace XWindowLib
{
    std::shared_ptr<ColorManager> ColorManager::s_colorManager;

    std::shared_ptr<ColorManager> ColorManager::GetColorManager(std::shared_ptr<Display> display)
    {
        if (!ColorManager::s_colorManager)
        {
            ColorManager::s_colorManager = std::make_shared<ColorManager>(display);
        }
        return ColorManager::s_colorManager;
    }

    ColorManager::ColorManager(std::shared_ptr<Display> display)
    {
        m_display = display;
        m_colormap = XDefaultColormap(m_display.get(), 0);
    }

    XColor ColorManager::GetXColor(const Color& color)
    {
        auto xcolorIterator = m_colorDictionary.find(color);
        XColor xcolor;
        if (xcolorIterator == m_colorDictionary.end())
        {
            xcolor = color.ToXColor();
            XAllocColor(m_display.get(), m_colormap, &xcolor);
            m_colorDictionary[color] = xcolor;
        }
        else
        {
            xcolor = (*xcolorIterator).second;
        }
        

        return xcolor;
    }
}