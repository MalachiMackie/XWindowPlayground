#include "TextBox.h"

#include <cstring>
#include <iostream>
#include "Types/Shapes/Square.h"
#include "Core/FontManager.h"

namespace XWindowLib
{
    TextBox::TextBox(Position position, Dimensions dimensions, std::string content, int borderWidth)
        : m_position{position}, m_dimensions{dimensions}, m_content{content}, m_borderWidth{borderWidth}
    {
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
        Widget::Init(display, window);
        InitFontManager(display);
        m_graphicsContext = XCreateGC(m_display.get(), *m_window, 0, nullptr);
                
        std::shared_ptr<XFontStruct> font = m_fontManager->GetFont(m_fontName);
        
        XSetFont(m_display.get(), m_graphicsContext, font->fid);
    }

    void TextBox::Draw()
    {
        if (m_display && m_window)
        {
            Widget::Draw();
            int textWidth = m_fontManager->GetTextWidth(m_fontName, m_content);
            XDrawText(m_display.get(),
            *m_window,
            m_graphicsContext,
            m_position.x + ((m_dimensions.width - textWidth) / 2),
            m_position.y + (m_dimensions.height + m_fontManager->GetFontHeight(m_fontName)) / 2,
            &m_textItem,
            1);
        }
    }

    TextBox::~TextBox()
    {
        delete m_textItem.chars;
    }
}