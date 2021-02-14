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
        m_textItem.nchars = m_content.size();
        m_textItem.chars = new char[m_content.length()];
        
        strcpy(m_textItem.chars, m_content.c_str());
    }

    void TextBox::Init(std::shared_ptr<Display> display, std::shared_ptr<Window> window)
    {
        if (m_isInitialized)
        {
            return;
        }
        Widget::Init(display, window);
        InitFontManager(display);
        m_graphicsContext = XCreateGC(m_display.get(), *m_window, 0, nullptr);
                
        const auto& font = m_fontManager->GetFont(m_fontName);
        
        XSetFont(m_display.get(), m_graphicsContext, font->fid);

        if (m_dimensions.height <= 0)
        {
            m_dimensions.height = font->max_bounds.ascent + font->max_bounds.descent;
        }
        if (m_dimensions.width <= 0)
        {
            m_dimensions.width = m_fontManager->GetTextWidth(m_fontName, m_content);
        }
        if (m_borderWidth > 0)
        {
            const std::unique_ptr<Drawable>& border = m_drawables[m_borderIndex];
            border->SetDimensions(m_dimensions);
            border->SetPosition(m_position);
        }
    }

    void TextBox::Draw()
    {
        if (m_display && m_window)
        {
            Widget::Draw();
            int textWidth = m_fontManager->GetTextWidth(m_fontName, m_content);
            int textHeight = m_fontManager->GetFontHeight(m_fontName);
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
            &m_textItem,
            1);
        }
    }

    TextBox::~TextBox()
    {
        delete m_textItem.chars;
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
        m_dimensions = dimensions;
        if (m_borderIndex >= 0) {
            const auto& border = m_drawables[m_borderIndex];
            border->SetDimensions(m_dimensions);
        }
    }
}