#include "Drawable.h"

namespace XWindowPlayground
{
    void Drawable::Init(Display* display, Window* window)
    {
        m_display = display;
        m_window = window;
        m_isInitialized = true;
    }
}