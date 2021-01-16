#include <X11/Xlib.h>
#include <iostream>
#include <memory>

#include "Button.h"
#include "../Shapes/Shape.h"
#include "../Shapes/Square.h"

namespace XWindowPlayground
{
    Button::Button(int x, int y, int width, int height, int shadowDistance)
        : m_x{x}, m_y{y}, m_width{width}, m_height{height}, m_shadowDistance{shadowDistance}
    {
        auto main = std::make_unique<Square>(m_x, m_y, m_width, m_height);
        main->Fill();
        
        if (m_shadowDistance > 0)
        {
            auto shadow = std::make_unique<Square>(m_x - m_shadowDistance, m_y - m_shadowDistance, m_width, m_height);
            shadow->Fill();
            m_shadowIndex = m_shapes.size();
            m_shapes.push_back(std::move(shadow));
        }
        
        m_mainIndex = m_shapes.size();
        m_shapes.push_back(std::move(main));
    }

    void Button::ApplyColor(Color color)
    {
        m_currentColor = color;
        m_shapes[m_mainIndex]->SetColor(m_currentColor);
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