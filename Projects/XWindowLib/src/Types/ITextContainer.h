#ifndef I_TEXT_CONTAINER
#define I_TEXT_CONTAINER

#include <X11/Xlib.h>
#include <memory>
#include <string>
#include "Core/FontManager.h"


namespace XWindowLib
{
    class ITextConatiner
    {
    protected:
        XTextItem m_textItem;
        std::shared_ptr<FontManager> m_fontManager;
        std::string m_fontName = "8x13bold";

        void InitFontManager(std::shared_ptr<Display> display) {m_fontManager = FontManager::GetFontManager(display);}

    public:
    };
}

#endif