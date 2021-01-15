#include <X11/Xlib.h>
#include <iostream>

#include "Button.h"
#include "../Shapes/Shape.h"
#include "../Shapes/Square.h"

namespace XWindowPlayground
{
    Button::Button(int x, int y, int width, int height, int shadowDistance)
        : m_x{x}, m_y{y}, m_width{width}, m_height{height}, m_shadowDistance{shadowDistance}
    {
        m_main = new Square{m_x, m_y, m_width, m_height};
        m_main->Fill();
        
        if (m_shadowDistance > 0)
        {
            m_shadow = new Square{m_x - m_shadowDistance, m_y - m_shadowDistance, m_width, m_height};
            m_shadow->Fill();
            m_shapes.push_back(m_shadow);
        }
        
        m_shapes.push_back(m_main);
    }

    void Button::ApplyColor(Color color)
    {
        m_currentColor = color;
        m_main->SetColor(m_currentColor);
    }

    void Button::SetColor(Color color)
    {
        m_color = color;
        ApplyColor(m_color);
    }

    void Button::SetColor(int r, int g, int b)
    {
        SetColor(Color{r, g, b});
    }

    void Button::OnHover()
    {
        ApplyColor(m_hoverColor);
    }

    void Button::OnStopHover()
    {
        ApplyColor(m_color);
    }

    bool Button::IsHovering(int mouseX, int mouseY)
    {
        return mouseX >= m_x
            && mouseX <= m_x + m_width
            && mouseY >= m_y
            && mouseY <= m_y + m_height;
    }

    void Button::OnClick()
    { 
        if (m_onClick)
        {
            m_onClick();
        }
    }

    void Button::OnLeftClick()
    {
        if (m_onLeftClick)
        {
            m_onLeftClick();
        }
    }

    void Button::OnMiddleClick()
    {
        if (m_onMiddleClick)
        {
            m_onMiddleClick();
        }
    }

    void Button::OnRightClick()
    {
        if (m_onRightClick)
        {
            m_onRightClick();
        }
    }
}