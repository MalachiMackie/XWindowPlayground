#ifndef I_HAVE_COLOR_H
#define I_HAVE_COLOR_H

#include "Color.h"

namespace XWindowLib
{
    class IHaveColor
    {
    protected:
        Color m_color = {0, 0, 0};
    public:
        virtual void SetColor(Color) = 0;
    };
}

#endif