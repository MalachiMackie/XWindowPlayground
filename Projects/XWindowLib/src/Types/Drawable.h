#ifndef DRAWABLE_H
#define DRAWABLE_H

#include <X11/Xlib.h>
#include <memory>

#include "Types/VerticalAlignment.h"
#include "Utils/Pairs.h"

namespace XWindowLib
{
    class Drawable
    {
    protected:
        std::shared_ptr<Display> m_display;
        std::shared_ptr<Window> m_window;

        bool m_isInitialized = false;

        VerticalAlignment m_verticalAlignment;
        Position m_position;
        Dimensions m_dimensions;

    public:
        virtual void Draw() = 0;
        virtual void Init(std::shared_ptr<Display> display, std::shared_ptr<Window> window);

        virtual void SetPosition(Position position) { m_position = position; }
        virtual void SetDimensions(Dimensions dimensions) { m_dimensions = dimensions; }

        const Position& GetPosition() { return m_position; }
        const Dimensions& GetDimensions() { return m_dimensions; }
        const VerticalAlignment& GetVerticalAlignment() { return m_verticalAlignment; }

        void SetVerticalAlignment(VerticalAlignment verticalAlignment) { m_verticalAlignment = verticalAlignment; }
    };
}

#endif