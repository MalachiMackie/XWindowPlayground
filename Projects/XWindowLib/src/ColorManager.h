#ifndef COLOR_MANAGER_H
#define COLOR_MANAGER_H

#include <map>
#include <X11/Xlib.h>
#include "Color.h"


namespace XWindowPlayground
{
    class ColorManager
    {
    private:
        std::map<Color, XColor> m_colorDictionary;
        Colormap m_colormap;
        Display* m_display;

        static ColorManager* s_colorManager;

    public:
        ColorManager(Display* display);
        ~ColorManager();

        XColor GetXColor(const Color& color);

        static ColorManager* GetColorManager(Display* display);
    };
}

#endif