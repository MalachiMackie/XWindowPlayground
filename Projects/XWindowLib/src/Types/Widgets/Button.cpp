#include "Button.h"

#include <X11/Xlib.h>
#include <iostream>
#include <memory>
#include <iostream>

#include "Types/Shapes/Shape.h"
#include "Types/Shapes/Square.h"
#include "Types/Shapes/Line.h"
#include "Types/Shapes/Arc.h"
#include "Types/Widgets/TextBox.h"

namespace XWindowLib
{
    const Color Button::s_defaultColor = {65000, 0, 0};

    Button::Button(Position position, Dimensions dimensions)
        : Button{Style{}, position, dimensions}
        {}

    Button::Button(Style style, Position position, Dimensions dimensions, std::unique_ptr<Drawable>&& drawable)
        : Button{style, position, dimensions}
    {
        AddDrawable(std::move(drawable), &m_contentIndex);

        ApplyStyle(m_style);
    }

    Button::Button(Style style, Position position, Dimensions dimensions)
        : m_style{style}
    {
        SetPosition(position);
        SetDimensions(dimensions);

        CreateButton();

        ApplyStyle(m_style);
    }

    Button::Button(Style style, Position position, Dimensions dimensions, std::string content)
        : Button{style, position, dimensions}
    {
        if (content.length() > 0)
        {
            auto textBox = std::make_unique<TextBox>(
                m_position, Dimensions::AUTO, content, TextAlignment::CENTER, VerticalAlignment::MIDDLE
            );
            AddDrawable(std::move(textBox), &m_contentIndex);
        }

        ApplyStyle(m_style);
    }
    
    void Button::SetText(std::string text)
    {
        Dimensions textDimensions;
        if (m_contentIndex < 0)
        {
            auto textBox = std::make_unique<TextBox>(
                m_position, Dimensions{true}, text, TextAlignment::CENTER, VerticalAlignment::MIDDLE
            );
            AddDrawable(std::move(textBox), &m_contentIndex);
            textDimensions = m_drawables[m_contentIndex]->GetDimensions();
        }
        else
        {
            const auto& drawable = m_drawables[m_contentIndex];
            auto* textContainer = dynamic_cast<ITextContainer*>(drawable.get());
            textContainer->SetText(text);
            textDimensions = drawable->GetDimensions();

        }
        if (m_dimensions.automatic)
        {
            SetDimensions(Dimensions{textDimensions.width + m_padding.left + m_padding.right, m_dimensions.height, m_dimensions.automatic});
            UpdateSize();
        }
        
        Draw();
    }

    void Button::SetDimensions(Dimensions dimensions)
    {
        Drawable::SetDimensions(dimensions);
        if (m_contentIndex >= 0)
        {
            const auto& drawable = m_drawables[m_contentIndex];
            if (!m_dimensions.automatic)
            {
                drawable->SetMaxDimensions(m_dimensions);
            }
            else
            {
                const auto& textBoxDimensions = drawable->GetDimensions();
                Dimensions tempDimensions = m_dimensions;
                if (textBoxDimensions.height > tempDimensions.height)
                {
                    tempDimensions.height = textBoxDimensions.height;
                }
                if (textBoxDimensions.width > tempDimensions.width)
                {
                    tempDimensions.width = textBoxDimensions.width;
                }
                Drawable::SetDimensions(tempDimensions);
            }
        }
        Draw();
    }

    void Button::SetContentPosition()
    {
        if (m_contentIndex < 0)
            return;

        const std::unique_ptr<Drawable>& drawable = m_drawables[m_contentIndex];
        if (!drawable)
            return;
        
        Dimensions dimensions = drawable->GetDimensions();
        Position position = drawable->GetPosition();
        switch (drawable->GetVerticalAlignment())
        {
        default:
        case VerticalAlignment::TOP:
            position.y = m_position.y;
            break;
        case VerticalAlignment::MIDDLE:
            position.y = m_position.y + (m_dimensions.height - dimensions.height) / 2;
            break;
        case VerticalAlignment::BOTTOM:
            position.y = m_position.y + m_dimensions.height - dimensions.height;
            break;
        }

        ITextContainer* textContainer = dynamic_cast<ITextContainer*>(drawable.get());
        if (textContainer)
        {
            switch(textContainer->GetTextAlignment())
            {
            case TextAlignment::LEFT:
                position.x = m_position.x + m_padding.left;
                break;
            
            case TextAlignment::CENTER:
            {
                if (m_dimensions.automatic)
                {
                    position.x = m_position.x + m_padding.left;
                }
                else
                {
                    position.x = m_position.x + (m_dimensions.width - dimensions.width) / 2;
                }
                break;
            }
            case TextAlignment::RIGHT:
                position.x = m_position.x + m_dimensions.width - dimensions.width;
                break;
            }   
        }
        
        drawable->SetPosition(position);
        if (m_dimensions.automatic)
        {
            SetDimensions(Dimensions{dimensions.width + m_padding.left + m_padding.right, m_dimensions.height, true});
        }
    }

    void Button::Init(std::shared_ptr<Display> display, std::shared_ptr<Window> window)
    {
        Widget::Init(display, window);
        SetContentPosition();
        UpdateSize();
    }

    void Button::UpdateSize()
    {
        if (m_topIndex >= 0)
        {
            Line* top = dynamic_cast<Line*>(m_drawables[m_topIndex].get());
            top->SetPosition1(Position{m_position.x + m_style.borderRadius, m_position.y});
            top->SetPosition2(Position{m_position.x - m_style.borderRadius + m_dimensions.width, m_position.y});
        }
        if (m_bottomIndex >= 0)
        {
            Line* bottom = dynamic_cast<Line*>(m_drawables[m_bottomIndex].get());
            bottom->SetPosition1(Position{m_position.x + m_style.borderRadius, m_position.y + m_dimensions.height});
            bottom->SetPosition2(Position{m_position.x - m_style.borderRadius + m_dimensions.width, m_position.y + m_dimensions.height});
        }
        if (m_leftIndex >= 0)
        {
            Line* left = dynamic_cast<Line*>(m_drawables[m_leftIndex].get());
            left->SetPosition1(Position{m_position.x, m_position.y + m_style.borderRadius});
            left->SetPosition2(Position{m_position.x, m_position.y + m_dimensions.height - m_style.borderRadius});
        }
        if (m_rightIndex >= 0)
        {
            Line* right = dynamic_cast<Line*>(m_drawables[m_rightIndex].get());
            right->SetPosition1(Position{m_position.x + m_dimensions.width, m_position.y + m_style.borderRadius});
            right->SetPosition2(Position{m_position.x + m_dimensions.width, m_position.y + m_dimensions.height - m_style.borderRadius});
        }

        if (m_fill1Index >= 0)
        {
            const auto& fill1 = m_drawables[m_fill1Index];
            fill1->SetPosition(Position{m_position.x, m_position.y + m_style.borderRadius});
            fill1->SetDimensions(Dimensions{m_dimensions.width, m_dimensions.height - (m_style.borderRadius * 2)});
        }

        if (m_fill2Index >= 0)
        {
            const auto& fill2 = m_drawables[m_fill2Index];
            fill2->SetPosition(Position{m_position.x + m_style.borderRadius, m_position.y});
            fill2->SetDimensions(Dimensions{m_dimensions.width - m_style.borderRadius * 2, m_dimensions.height});
        }

        if (m_style.borderRadius > 0)
        {
            Dimensions arcDimensions{m_style.borderRadius * 2, m_style.borderRadius * 2};
            auto topLeftPosition = m_position;
            auto topRightPosition = Position{m_position.x + m_dimensions.width - m_style.borderRadius * 2, m_position.y};
            auto bottomLeftPosition = Position{m_position.x, m_position.y + m_dimensions.height - m_style.borderRadius * 2};
            auto bottomRightPosition = Position{m_position.x + m_dimensions.width - m_style.borderRadius * 2, m_position.y + m_dimensions.height - m_style.borderRadius * 2};

            if (m_topLeftCornerIndex >= 0)
            {
                m_drawables[m_topLeftCornerIndex]->SetPosition(topLeftPosition);
            }
            if (m_topRightCornerIndex >= 0)
            {
                m_drawables[m_topRightCornerIndex]->SetPosition(topRightPosition);
            }
            if (m_bottomLeftCornerIndex >= 0)
            {
                m_drawables[m_bottomLeftCornerIndex]->SetPosition(bottomLeftPosition);
            }
            if (m_bottomRightCornerIndex >= 0)
            {
                m_drawables[m_bottomRightCornerIndex]->SetPosition(bottomRightPosition);
            }
        }
    }

    void Button::CreateButton()
    {
        auto left = std::make_unique<Line>();
        auto right = std::make_unique<Line>();
        auto bottom = std::make_unique<Line>();
        auto top = std::make_unique<Line>();

        auto fill1 = std::make_unique<Square>();
        fill1->Fill();
        auto fill2 = std::make_unique<Square>();
        fill2->Fill();

        if (m_style.borderRadius > 0)
        {
            Dimensions arcDimensions{m_style.borderRadius * 2, m_style.borderRadius * 2};
            auto topLeft = std::make_unique<Arc>(Position{}, arcDimensions,180, 90);
            topLeft->Fill();

            auto topRight = std::make_unique<Arc>(Position{}, arcDimensions, 270, 90);
            topRight->Fill();

            auto bottomLeft = std::make_unique<Arc>(Position{}, arcDimensions, 90, 90);
            bottomLeft->Fill();

            auto bottomRight = std::make_unique<Arc>(Position{},arcDimensions, 0, 90);
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
        AddDrawable(std::move(fill1), &m_fill1Index);
        AddDrawable(std::move(fill2), &m_fill2Index);

        UpdateSize();
    }

    #pragma region hovering

    void Button::OnHover()
    {
        if (m_hasHoverStyle)
            ApplyStyle(m_hoverStyle);
    }

    void Button::OnStopHover()
    {
        if ((!m_hasClickStyle || !IsClicking()) && m_hasHoverStyle)
            ApplyStyle(m_style);
    }

    bool Button::IsHovering(int mouseX, int mouseY)
    {
        return mouseX >= m_position.x
            && mouseX <= m_position.x + m_dimensions.width
            && mouseY >= m_position.y
            && mouseY <= m_position.y + m_dimensions.height;
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
        if (m_style != style)
        {
            m_style = style;
            ApplyStyle(m_style);
        }
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
                haveColor->SetColor(m_currentColor);
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

    bool Button::TryGetTextAlignment(TextAlignment* outTextAlignment)
    {
        if (m_contentIndex >= 0)
        {
            const auto& drawable = m_drawables[m_contentIndex];
            ITextContainer* textContainer = dynamic_cast<ITextContainer*>(drawable.get());
            if (textContainer)
            {
                *outTextAlignment = textContainer->GetTextAlignment();
                return true;
            }
        }

        return false;
    }

    bool Button::TryGetTextVerticalAlignment(VerticalAlignment* outVerticalAlignment)
    {
        if (m_contentIndex < 0)
            return false;

        const auto& drawable = m_drawables[m_contentIndex];
        *outVerticalAlignment = drawable->GetVerticalAlignment();
        return true;
    }


    void Button::SetTextAlignment(TextAlignment textAlignment)
    {
        if (m_contentIndex >= 0)
        {
            const auto& drawable = m_drawables[m_contentIndex];
            ITextContainer* textContainer = dynamic_cast<ITextContainer*>(drawable.get());
            if (textContainer)
            {
                textContainer->SetTextAlignment(textAlignment);
                SetContentPosition();
                Draw();
            }
        }
    }

    void Button::SetTextVerticalAlignment(VerticalAlignment verticalAlignment)
    {
        if (m_contentIndex >= 0)
        {
            const auto& drawable = m_drawables[m_contentIndex];
            drawable->SetVerticalAlignment(verticalAlignment);
            SetContentPosition();
            Draw();
        }
    }


    #pragma endregion
}