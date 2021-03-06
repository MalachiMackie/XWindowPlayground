#ifndef DRAWABLE_H
#define DRAWABLE_H

#include <X11/Xlib.h>
#include <memory>
#include <functional>

#include "Types/VerticalAlignment.h"
#include "Utils/Pairs.h"

namespace XWindowLib
{
    class Drawable
    {
    private:
        std::function<void(void)> m_onDraw;

    protected:
        std::shared_ptr<Display> m_display;
        std::shared_ptr<Window> m_window;

        bool m_isInitialized = false;

        VerticalAlignment m_verticalAlignment;
        Position m_position;
        Dimensions m_dimensions;
        Dimensions m_maxDimensions = Dimensions{50000, 50000};
        Margin m_margin;

    public:
        virtual void Draw();
        virtual void Init(std::shared_ptr<Display> display, std::shared_ptr<Window> window);

        virtual void SetPosition(Position position) { m_position = position; }
        virtual void SetDimensions(Dimensions dimensions);
        void SetMaxDimensions(Dimensions dimensions);

        const Margin& GetMargin() { return m_margin; }
        const Position& GetPosition() { return m_position; }
        const Dimensions& GetDimensions() { return m_dimensions; }
        const VerticalAlignment& GetVerticalAlignment() { return m_verticalAlignment; }

        void SetMargin(const Margin& margin) { m_margin = margin; }
        void SetVerticalAlignment(VerticalAlignment verticalAlignment) { m_verticalAlignment = verticalAlignment; }
        void SetOnDraw(std::function<void(void)> onDraw) { m_onDraw = onDraw; }
    };
}

#endif