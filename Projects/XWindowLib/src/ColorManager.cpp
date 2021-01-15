#include "ColorManager.h"

namespace XWindowPlayground
{
    ColorManager* ColorManager::s_colorManager;

    ColorManager* ColorManager::GetColorManager(Display* display)
    {
        if (!ColorManager::s_colorManager)
        {
            ColorManager::s_colorManager = new ColorManager(display);
        }
        return ColorManager::s_colorManager;
    }

    ColorManager::ColorManager(Display* display)
    {
        m_display = display;
        m_colormap = XDefaultColormap(m_display, 0);
    }

    XColor ColorManager::GetXColor(const Color& color)
    {
        auto xcolorIterator = m_colorDictionary.find(color);
        XColor xcolor;
        if (xcolorIterator == m_colorDictionary.end())
        {
            xcolor = color.ToXColor();
            XAllocColor(m_display, m_colormap, &xcolor);
            m_colorDictionary[color] = xcolor;
        }
        else
        {
            xcolor = (*xcolorIterator).second;
        }
        

        return xcolor;
    }
}