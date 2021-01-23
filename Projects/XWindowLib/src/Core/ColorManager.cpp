#include "ColorManager.h"

#include <iostream>

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
        m_colorMap = XDefaultColormap(m_display.get(), 0);
    }

    XColor ColorManager::GetXColor(const Color& color)
    {
        if (m_colorDictionary.find(color) == m_colorDictionary.end())
        {
            XColor xcolor = color.ToXColor();
            XAllocColor(m_display.get(), m_colorMap, &xcolor);
            m_colorDictionary[color] = xcolor;
            return xcolor;
        }
        else
        {
            return m_colorDictionary[color];
        }
    }

    ColorManager::~ColorManager()
    {
        XFreeColormap(m_display.get(), m_colorMap);
        m_colorDictionary.clear();
    }
}