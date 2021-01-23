#ifndef TEXT_BOX_H
#define TEXT_BOX_H

#include <X11/Xlib.h>
#include <string>
#include "Types/Widgets/Widget.h"
#include "Types/ITextContainer.h"
#include "Utils/Pairs.h"

namespace XWindowLib
{
    class TextBox : public Widget, public ITextContainer
    {
    private:
        Position m_position;
        Dimensions m_dimensions;
        std::string m_content;
        int m_borderWidth;

        int m_borderIndex;
        GC m_graphicsContext;

    public:
        TextBox(Position position, Dimensions dimensions, std::string content, TextAlignment textAlignment = TextAlignment::LEFT, int borderWidth = 0);

        virtual void Init(std::shared_ptr<Display> display, std::shared_ptr<Window> window) override;
        virtual void Draw() override;

        virtual ~TextBox() override;
    };
}

#endif