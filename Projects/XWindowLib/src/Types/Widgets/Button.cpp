#include "Button.h"

#include <X11/Xlib.h>
#include <iostream>
#include <memory>

#include "Types/Shapes/Shape.h"
#include "Types/Shapes/Square.h"
#include "Types/Shapes/Line.h"
#include "Types/Shapes/Arc.h"

namespace XWindowLib
{
    const Color Button::s_defaultColor = {65000, 0, 0};

    Button::Button(Style style)
        : m_style{style}
    {
        auto left = std::make_unique<Line>(
            Position{m_style.position.x, m_style.position.y + m_style.borderRadius},
            Position{m_style.position.x, m_style.position.y + m_style.dimensions.height - m_style.borderRadius}
        );
        auto right = std::make_unique<Line>(
            Position{m_style.position.x + m_style.dimensions.width, m_style.position.y + m_style.borderRadius},
            Position{m_style.position.x + m_style.dimensions.width, m_style.position.y + m_style.dimensions.height - m_style.borderRadius}
        );
        auto bottom = std::make_unique<Line>(
            Position{m_style.position.x + m_style.borderRadius, m_style.position.y + m_style.dimensions.height},
            Position{m_style.position.x - m_style.borderRadius + m_style.dimensions.width, m_style.position.y + m_style.dimensions.height}
        );
        auto top = std::make_unique<Line>(
            Position{m_style.position.x + m_style.borderRadius, m_style.position.y},
            Position{m_style.position.x - m_style.borderRadius + m_style.dimensions.width, m_style.position.y}
        );

        auto fill1 = std::make_unique<Square>(m_style.position.x, m_style.position.y + m_style.borderRadius, m_style.dimensions.width, m_style.dimensions.height - (m_style.borderRadius * 2));
        fill1->Fill();
        auto fill2 = std::make_unique<Square>(m_style.position.x + m_style.borderRadius, m_style.position.y, m_style.dimensions.width - m_style.borderRadius * 2, m_style.dimensions.height);
        fill2->Fill();

        if (style.borderRadius > 0)
        {
            auto topLeft = std::make_unique<Arc>(m_style.position.x, m_style.position.y, m_style.borderRadius * 2, m_style.borderRadius * 2, 180, 90);
            topLeft->Fill();
            auto topRight = std::make_unique<Arc>(m_style.position.x + m_style.dimensions.width - m_style.borderRadius * 2, m_style.position.y, m_style.borderRadius * 2, m_style.borderRadius * 2, 270, 90);
            topRight->Fill();
            auto bottomLeft = std::make_unique<Arc>(m_style.position.x, m_style.position.y + m_style.dimensions.height - m_style.borderRadius * 2, m_style.borderRadius * 2, m_style.borderRadius * 2, 90, 90);
            bottomLeft->Fill();
            auto bottomRight = std::make_unique<Arc>(m_style.position.x + m_style.dimensions.width - m_style.borderRadius * 2, m_style.position.y + m_style.dimensions.height - m_style.borderRadius * 2, m_style.borderRadius * 2, m_style.borderRadius * 2, 0, 90);
            bottomRight->Fill();

            AddDrawable(std::move(topLeft), &m_topLeftCornerIndex);
            AddDrawable(std::move(topRight), &m_topRightCornerIndex);
            AddDrawable(std::move(bottomLeft), &m_bottomLeftCornerIndex);
            AddDrawable(std::move(bottomRight), &m_bottomRightCornerIndex);
        }

        AddDrawable(std::move(top), &m_topIndex);
        AddDrawable(std::move(bottom), &m_bottomIndex);
        AddDrawable(std::move(right), &m_rightIndex);
        AddDrawable(std::move(left), &m_leftIndex);
        AddDrawable(std::move(fill1), &m_fill1);
        AddDrawable(std::move(fill2), &m_fill2);

        ApplyStyle(m_style);
    }

    Button::Button(int x, int y, int width, int height)
        : Button{Style{Button::s_defaultColor, {x, y}, {width, height}}}
    {
        
    }

    #pragma region hovering

    void Button::OnHover()
    {
        if (m_hasHoverStyle)
            ApplyStyle(m_hoverStyle);
    }

    void Button::OnStopHover()
    {
        if (!m_hasClickStyle || !IsClicking() && m_hasHoverStyle)
            ApplyStyle(m_style);
    }

    bool Button::IsHovering(int mouseX, int mouseY)
    {
        return mouseX >= m_style.position.x
            && mouseX <= m_style.position.x + m_style.dimensions.width
            && mouseY >= m_style.position.y
            && mouseY <= m_style.position.y + m_style.dimensions.height;
    }

    #pragma endregion

    #pragma region clicks

    void Button::OnClick()
    { 
        if (m_onClick)
        {
            m_onClick();
        }

        if (m_hasClickStyle)
        {
            ApplyStyle(m_clickStyle);
        }
    }

    void Button::OnClickRelease()
    {
        if (m_hasClickStyle)
        {
            if (m_isHovering && m_hasHoverStyle)
                ApplyStyle(m_hoverStyle);
            else
                ApplyStyle(m_style);
        }

        if (m_onClickRelease) m_onClickRelease();
    }

    void Button::OnLeftClickRelease(){if (m_onLeftClickRelease) m_onLeftClickRelease();}
    void Button::OnMiddleClickRelease(){if (m_onMiddleClickRelease) m_onMiddleClickRelease();}
    void Button::OnRightClickRelease(){if (m_onRightClickRelease) m_onRightClickRelease();}

    void Button::OnLeftClick(){if (m_onLeftClick) m_onLeftClick();}
    void Button::OnMiddleClick(){if (m_onMiddleClick) m_onMiddleClick();}
    void Button::OnRightClick(){if (m_onRightClick) m_onRightClick();}

    #pragma endregion

    #pragma region styles
    void Button::ApplyStyle(const Style& style)
    {
        m_currentStyle = style;

        for (auto &&drawable : m_drawables)
        {
            IHaveColor* haveColor = dynamic_cast<IHaveColor*>(drawable.get());
            if (haveColor)
                haveColor->SetColor(m_currentStyle.color);
        }
        
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

    void Button::SetClickStyle(Style style)
    {
        m_clickStyle = style;
        m_hasClickStyle = true;
    }

    void Button::ApplyColor(Color color)
    {
        m_currentColor = color;
        for (auto &&drawable : m_drawables)
        {
            IHaveColor* haveColor = dynamic_cast<IHaveColor*>(drawable.get());
            if (haveColor)
                haveColor->SetColor(m_currentStyle.color);
        }
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

    #pragma endregion
}