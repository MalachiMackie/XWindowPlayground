#ifndef BUTTON_H
#define BUTTON_H

#include <functional>

#include "Widgets/Widget.h"
#include "Utils/Pairs.h"
#include "Types/Clickable.h"
#include "Core/Color.h"

namespace XWindowLib
{
    class Button : public Widget, public Clickable
    {
    public:
        struct Style
        {
            Color color;
            Position position;
            Dimensions dimensions;
            int borderRadius = 0;
        public:
            Style(){};
            Style(Color color, std::pair<int, int> position, std::pair<int, int> dimensions)
            {
                Style::color = color;
                Style::position = position;
                Style::dimensions = dimensions;
            }
        };

    private:
        Style m_style;
        Style m_hoverStyle;
        Style m_clickStyle;
        Style m_currentStyle;
        
        bool m_hasHoverStyle = false;
        bool m_hasClickStyle = false;

        int m_leftIndex;
        int m_rightIndex;
        int m_topIndex;
        int m_bottomIndex;

        int m_topLeftCornerIndex;
        int m_topRightCornerIndex;
        int m_bottomLeftCornerIndex;
        int m_bottomRightCornerIndex;

        int m_fill1;
        int m_fill2;

        Color m_currentColor;

        std::function<void(void)> m_onClick;
        std::function<void(void)> m_onLeftClick;
        std::function<void(void)> m_onRightClick;
        std::function<void(void)> m_onMiddleClick;

        std::function<void(void)> m_onClickRelease;
        std::function<void(void)> m_onLeftClickRelease;
        std::function<void(void)> m_onRightClickRelease;
        std::function<void(void)> m_onMiddleClickRelease;

        static const Color s_defaultColor;
        
    private:
        void ApplyColor(Color color);
        void ApplyStyle(const Style& style);

    public:
        Button(int x, int y, int width, int height);
        Button(Style style);

        virtual void OnHover() override;
        virtual void OnStopHover() override;
        virtual bool IsHovering(int mouseX, int mouseY) override;

        virtual void OnClick() override;
        virtual void OnLeftClick() override;
        virtual void OnMiddleClick() override;
        virtual void OnRightClick() override;

        virtual void OnClickRelease() override;
        virtual void OnLeftClickRelease() override;
        virtual void OnRightClickRelease() override;
        virtual void OnMiddleClickRelease() override;

        void SetOnClick(std::function<void(void)> onClick) { m_onClick = onClick; }
        void SetOnLeftClick(std::function<void(void)> onLeftClick) { m_onLeftClick = onLeftClick; }
        void SetOnRightClick(std::function<void(void)> onRightClick) { m_onRightClick = onRightClick; }
        void SetOnMiddleClick(std::function<void(void)> onMiddleClick) { m_onMiddleClick = onMiddleClick; }

        void SetOnClickRelease(std::function<void(void)> onClickRelease) { m_onClickRelease = onClickRelease; }
        void SetOnLeftClickRelease(std::function<void(void)> onLeftClickRelease) { m_onLeftClickRelease = onLeftClickRelease; }
        void SetOnRightClickRelease(std::function<void(void)> onRightClickRelease) { m_onRightClickRelease = onRightClickRelease; }
        void SetOnMiddleClickRelease(std::function<void(void)> onMiddleClickRelease) { m_onMiddleClickRelease = onMiddleClickRelease; }
    
        void SetColor(Color color);
        void SetColor(int r, int g, int b);

        void SetStyle(Button::Style style);
        void SetHoverStyle(Button::Style style);
        void SetClickStyle(Button::Style style);
    };
}

#endif