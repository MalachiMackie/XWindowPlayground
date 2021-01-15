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
    private:
        int m_x, m_y;
        int m_width, m_height;
        int m_shadowDistance;

        Shape* m_main;
        Shape* m_shadow;

        Color m_color;
        Color m_hoverColor{0, 65000, 0};
        Color m_currentColor;

        std::function<void(void)> m_onClick;
        std::function<void(void)> m_onLeftClick;
        std::function<void(void)> m_onRightClick;
        std::function<void(void)> m_onMiddleClick;
        
    private:
        void ApplyColor(Color color);

    public:
        Button(int x, int y, int width, int height, int shadowDistance = 2);

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
    };
}

#endif