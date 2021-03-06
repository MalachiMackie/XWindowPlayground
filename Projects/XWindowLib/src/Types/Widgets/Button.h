#ifndef BUTTON_H
#define BUTTON_H

#include <functional>

#include "Types/Widgets/Widget.h"
#include "Utils/Pairs.h"
#include "Types/Clickable.h"
#include "Core/Color.h"
#include "Types/ITextContainer.h"

namespace XWindowLib
{
    class Button : public Widget, public Clickable
    {
    public:
        struct Style
        {
            Color color;
            int borderRadius = 0;

            bool operator==(Style other)
            {
                return borderRadius == other.borderRadius
                    && color == other.color;
            }

            bool operator!=(Style other)
            {
                return !(*this == other);
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

        int m_fill1Index;
        int m_fill2Index;

        int m_contentIndex = -1;

        Color m_currentColor;

        std::function<void(void)> m_onClick;
        std::function<void(void)> m_onLeftClick;
        std::function<void(void)> m_onRightClick;
        std::function<void(void)> m_onMiddleClick;

        std::function<void(void)> m_onClickRelease;
        std::function<void(void)> m_onLeftClickRelease;
        std::function<void(void)> m_onRightClickRelease;
        std::function<void(void)> m_onMiddleClickRelease;

        Padding m_padding = Padding{10, 0};

        static const Color s_defaultColor;
        
    private:
        void CreateButton();
        void ApplyColor(Color color);
        void ApplyStyle(const Style& style);
        void SetContentPosition();
        void UpdateSize();

    public:
        Button(Position position, Dimensions dimensions);
        Button(Style style, Position position, Dimensions dimensions);
        Button(Style style, Position position, Dimensions dimensions, std::string content);
        Button(Style style, Position position, Dimensions dimensions, std::unique_ptr<Drawable>&& drawable);

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

        bool TryGetTextAlignment(TextAlignment* outTextAlignment);
        bool TryGetTextVerticalAlignment(VerticalAlignment* outVerticalAlignment);

        void SetTextAlignment(TextAlignment textAlignment);
        void SetTextVerticalAlignment(VerticalAlignment verticalAlignment);

        void SetText(std::string text);

        virtual void SetDimensions(Dimensions dimensions) override;

        virtual void Init(std::shared_ptr<Display> display, std::shared_ptr<Window> window) override;
    };
}

#endif