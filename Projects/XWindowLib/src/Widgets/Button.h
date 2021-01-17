#ifndef BUTTON_H
#define BUTTON_H

#include <functional>

#include "Widget.h"
#include "../Clickable.h"
#include "../Color.h"

namespace XWindowPlayground
{
    class Button : public Widget, public Clickable
    {
    public:
        struct Style
        {
            Color color;
            Color shadowColor;
            std::pair<int, int> position;
            std::pair<int, int> dimensions;
            int shadowDepth;
        public:
            Style(){};
            Style(Color color, Color shadowColor, std::pair<int, int> position, std::pair<int, int> dimensions, int shadowDepth)
            {
                Style::color = color;
                Style::shadowColor = shadowColor;
                Style::position = position;
                Style::dimensions = dimensions;
                Style::shadowDepth = shadowDepth;
            }
        };

    private:
        Style m_style;
        Style m_hoverStyle;
        Style m_currentStyle;
        
        bool m_hasHoverStyle = false;

        int m_mainIndex;
        int m_shadowIndex;

        Color m_currentColor;

        std::function<void(void)> m_onClick;
        std::function<void(void)> m_onLeftClick;
        std::function<void(void)> m_onRightClick;
        std::function<void(void)> m_onMiddleClick;

        static const Color s_defaultColor;
        static const Color s_defaultShadowColor;
        
    private:
        void ApplyColor(Color color);
        void ApplyStyle(const Style& style);

    public:
        Button(int x, int y, int width, int height, int shadowDistance = 2);
        Button(Style style);

        virtual void OnHover() override;
        virtual void OnStopHover() override;
        virtual bool IsHovering(int mouseX, int mouseY) override;

        virtual void OnClick();
        virtual void OnLeftClick();
        virtual void OnMiddleClick();
        virtual void OnRightClick();

        void SetOnClick(std::function<void(void)> onClick) { m_onClick = onClick; }
        void SetOnLeftClick(std::function<void(void)> onLeftClick) { m_onLeftClick = onLeftClick; }
        void SetOnRightClick(std::function<void(void)> onRightClick) { m_onRightClick = onRightClick; }
        void SetOnMiddleClick(std::function<void(void)> onMiddleClick) { m_onMiddleClick = onMiddleClick; }
    
        void SetColor(Color color);
        void SetColor(int r, int g, int b);

        void SetStyle(Button::Style style);
        void SetHoverStyle(Button::Style style);
    };
}

#endif