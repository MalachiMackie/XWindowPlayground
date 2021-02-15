#include "Drawable.h"

namespace XWindowLib
{
    void Drawable::Init(std::shared_ptr<Display> display, std::shared_ptr<Window> window)
    {
        m_display = display;
        m_window = window;
        m_isInitialized = true;
    }

    void Drawable::Draw()
    {
        if (m_onDraw)
        {
            m_onDraw();
        }
    }
}