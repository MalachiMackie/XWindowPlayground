#include "TextBox.h"

#include <cstring>
#include <iostream>
#include "Types/Shapes/Square.h"
#include "Core/FontManager.h"

namespace XWindowLib
{
    TextBox::TextBox(Position position, Dimensions dimensions, std::string content, TextAlignment textAlignment, VerticalAlignment verticalAlignment, int borderWidth)
        : m_content{content}, m_borderWidth{borderWidth}
    {
        SetPosition(position);
        SetDimensions(dimensions);
        m_textAlignment = textAlignment;
        m_verticalAlignment = verticalAlignment;
        if (m_borderWidth > 0)
        {
            auto square = std::make_unique<Square>(position, dimensions);
            AddDrawable(std::move(square), &m_borderIndex);
        }
        m_textItem = new XTextItem;
        m_textItem->delta = 0;
        m_textItem->nchars = m_content.length();
        m_textItem->chars = new char[m_content.length()];
        
        strcpy(m_textItem->chars, m_content.c_str());
    }

    TextBox::TextBox(std::string content)
        : m_content{content}
    {
        SetPosition(Position{});
        SetDimensions(Dimensions::AUTO);
        m_textAlignment = TextAlignment::LEFT;
        m_verticalAlignment = VerticalAlignment::MIDDLE;

        m_textItem = new XTextItem;
        m_textItem->delta = 0;
        m_textItem->nchars = m_content.size();
        m_textItem->chars = new char[m_content.length()];

        strcpy(m_textItem->chars, m_content.c_str());
    }

    void TextBox::SetText(std::string text)
    {
        m_content = text;
        if (!m_textItem)
        {
            m_textItem = new XTextItem;
        }
        m_textItem->nchars = m_content.size();

        delete[] m_textItem->chars;

        m_textItem->chars = new char[m_content.length()];

        strcpy(m_textItem->chars, m_content.c_str());
        CalculateDimensions();
    }

    void TextBox::SetBorderWidth(int borderWidth)
    {
        if (borderWidth < 0)
        {
            throw "Border width must be greater than or equal to 0";
        }
        m_borderWidth = borderWidth;

        if (m_borderIndex < 0)
        {
            auto square = std::make_unique<Square>(m_position, m_dimensions);
            square->SetBorderWidth(m_borderWidth);
            AddDrawable(std::move(square), &m_borderIndex);
        }
        else
        {
            auto& drawable = m_drawables[m_borderIndex];
            Square* square = dynamic_cast<Square*>(drawable.get());
            if (square)
            {
                square->SetBorderWidth(m_borderWidth);
            }
        }
    }

    void TextBox::CalculateDimensions()
    {
        if (!m_isInitialized || !m_dimensions.automatic)
            return;

        Dimensions tempDimensions = m_dimensions;

        const auto& font = FontManager::GetFontManager(m_display).GetFont(m_fontName);
        tempDimensions.height = font->max_bounds.ascent + font->max_bounds.descent;
        tempDimensions.width = FontManager::GetFontManager(m_display).GetTextWidth(m_fontName, m_content);
        if (m_borderIndex >= 0)
        {
            const auto& border = m_drawables[m_borderIndex];
            border->SetDimensions(tempDimensions);
            border->SetPosition(m_position);
        }
        SetDimensions(tempDimensions);
    }

    void TextBox::Init(std::shared_ptr<Display> display, std::shared_ptr<Window> window)
    {
        if (m_isInitialized)
        {
            return;
        }
        Widget::Init(display, window);
        m_graphicsContext = XCreateGC(m_display.get(), *m_window, 0, nullptr);
                
        FontManager::GetFontManager(m_display).SetFont(m_graphicsContext, m_fontName);

        CalculateDimensions();
    }

    void TextBox::Draw()
    {
        if (m_isInitialized)
        {
            Widget::Draw();
            int textWidth = FontManager::GetFontManager(m_display).GetTextWidth(m_fontName, m_content);
            int textHeight = FontManager::GetFontManager(m_display).GetFontHeight(m_fontName);
            int x;
            int y = m_position.y + textHeight;
            switch (m_textAlignment)
            {
            default:
            case TextAlignment::LEFT:
                x = m_position.x;
                break;
            case TextAlignment::RIGHT:
                x = m_position.x + m_dimensions.width - textWidth;
                break;
            case TextAlignment::CENTER:
                x = m_position.x + ((m_dimensions.width - textWidth) / 2);
                break;
            }

            XDrawText(m_display.get(),
            *m_window,
            m_graphicsContext,
            x,
            y,
            m_textItem,
            1);
        }
    }

    void TextBox::SetPosition(Position position)
    { 
        m_position = position;
        if (m_borderIndex >= 0)
        {
            const auto& border = m_drawables[m_borderIndex];
            border->SetPosition(m_position);
        }
    }

    void TextBox::SetDimensions(Dimensions dimensions)
    {
        Drawable::SetDimensions(dimensions);
        if (m_borderIndex >= 0) {
            const auto& border = m_drawables[m_borderIndex];
            border->SetDimensions(m_dimensions);
        }
    }
}