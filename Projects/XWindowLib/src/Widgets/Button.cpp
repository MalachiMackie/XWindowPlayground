#include <X11/Xlib.h>
#include <iostream>
#include <memory>

#include "Button.h"
#include "../Shapes/Shape.h"
#include "../Shapes/Square.h"

namespace XWindowPlayground
{
    const Color Button::s_defaultColor = {65000, 0, 0};
    const Color Button::s_defaultShadowColor = {0, 0, 0};

    Button::Button(Style style)
        : m_style{style}
    {
        auto main = std::make_unique<Square>();
        main->Fill();

        auto shadow = std::make_unique<Square>(0, 0, 0, 0);
        shadow->Fill();
        m_shadowIndex = m_shapes.size();
        m_shapes.push_back(std::move(shadow));
        
        m_mainIndex = m_shapes.size();
        m_shapes.push_back(std::move(main));

        ApplyStyle(m_style);
    }

    Button::Button(int x, int y, int width, int height, int shadowDistance)
        : Button{Style{Button::s_defaultColor, Button::s_defaultShadowColor, {x, y}, {width, height}, shadowDistance}}
    {
        
    }

    void Button::ApplyColor(Color color)
    {
        m_currentColor = color;
        m_shapes[m_mainIndex]->SetColor(m_currentColor);
    }

    void Button::SetColor(Color color)
    {
        m_style.color = color;
        ApplyColor(m_style.color);
    }

    void Button::SetColor(int r, int g, int b)
    {
        SetColor(Color{r, g, b});
    }

    void Button::OnHover()
    {
        if (m_hasHoverStyle)
            ApplyStyle(m_hoverStyle);
    }

    void Button::OnStopHover()
    {
        if (m_hasHoverStyle)
            ApplyStyle(m_style);
    }

    bool Button::IsHovering(int mouseX, int mouseY)
    {
        return mouseX >= m_style.position.first
            && mouseX <= m_style.position.first + m_style.dimensions.first
            && mouseY >= m_style.position.second
            && mouseY <= m_style.position.second + m_style.dimensions.second;
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

    void Button::ApplyStyle(const Style& style)
    {
        m_currentStyle = style;

        Square* main = dynamic_cast<Square*>(m_shapes[m_mainIndex].get());
        main->Set(m_currentStyle.position.first, m_currentStyle.position.second, m_currentStyle.dimensions.first, m_currentStyle.dimensions.second);
        main->SetColor(m_currentStyle.color);

        Square* shadow = dynamic_cast<Square*>(m_shapes[m_shadowIndex].get());
        if (m_currentStyle.shadowDepth <= 0)
            shadow->Set(0, 0, 0, 0);
        else
            shadow->Set(m_currentStyle.position.first - m_currentStyle.shadowDepth, m_currentStyle.position.second - m_currentStyle.shadowDepth, m_currentStyle.dimensions.first, m_currentStyle.dimensions.second);
        shadow->SetColor(m_currentStyle.shadowColor);
        Draw();
    }

    void Button::SetStyle(Style style)
    {
        m_style = style;
        ApplyStyle(m_style);
    }

    void Button::SetHoverStyle(Style style)
    {
        m_hoverStyle = style;
        m_hasHoverStyle = true;
    }
}