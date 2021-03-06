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

    void Drawable::SetDimensions(Dimensions dimensions)
    {
        if (dimensions.height > m_maxDimensions.height)
            dimensions.height = m_maxDimensions.height;

        if (dimensions.width > m_maxDimensions.width)
            dimensions.width = m_maxDimensions.width;
        
        m_dimensions = dimensions;
    }

    void Drawable::SetMaxDimensions(Dimensions dimensions)
    {
        m_maxDimensions = dimensions;
        SetDimensions(m_dimensions);
    }
}