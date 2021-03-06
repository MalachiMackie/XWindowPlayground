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
        std::string m_content;
        int m_borderWidth = 0;

        int m_borderIndex = -1;
        GC m_graphicsContext;

    private:
        void CalculateDimensions();

    public:
        TextBox(std::string content);
        TextBox(Position position, Dimensions dimensions, std::string content, TextAlignment textAlignment = TextAlignment::LEFT, VerticalAlignment verticalAlignment = VerticalAlignment::TOP, int borderWidth = 0);

        virtual void Init(std::shared_ptr<Display> display, std::shared_ptr<Window> window) override;
        virtual void Draw() override;

        virtual void SetDimensions(Dimensions dimensions) override;
        virtual void SetPosition(Position position) override;
        void SetBorderWidth(int borderWidth);
        int GetBorderWidth() { return m_borderWidth; }

        virtual void SetText(std::string text) override;
        virtual const std::string& GetText() override { return m_content; }
    };
}

#endif