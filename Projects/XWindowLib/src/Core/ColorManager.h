#ifndef COLOR_MANAGER_H
#define COLOR_MANAGER_H

#include <map>
#include <X11/Xlib.h>
#include <memory>
#include "Core/Color.h"


namespace XWindowLib
{
    class ColorManager
    {
    private:
        std::map<Color, XColor> m_colorDictionary;
        Colormap m_colorMap;
        std::shared_ptr<Display> m_display;

        static std::shared_ptr<ColorManager> s_colorManager;

    public:
        ColorManager(std::shared_ptr<Display> display);
        ~ColorManager();

        XColor GetXColor(const Color& color);

        static std::shared_ptr<ColorManager> GetColorManager(std::shared_ptr<Display> display);
    };
}

#endif