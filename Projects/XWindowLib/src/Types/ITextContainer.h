#ifndef I_TEXT_CONTAINER
#define I_TEXT_CONTAINER

#include <X11/Xlib.h>
#include <memory>
#include <string>
#include "Core/FontManager.h"


namespace XWindowLib
{
    enum class TextAlignment
    {
        LEFT,
        RIGHT,
        CENTER
    };

    class ITextContainer
    {
    protected:
        XTextItem* m_textItem;
        std::string m_fontName = "8x13bold";
        TextAlignment m_textAlignment;

    public:

        const TextAlignment& GetTextAlignment() { return m_textAlignment; }
        void SetTextAlignment(TextAlignment textAlignment) { m_textAlignment = textAlignment; }
        
        virtual const std::string& GetText() = 0;
        virtual void SetText(std::string text) = 0;
    };
}

#endif