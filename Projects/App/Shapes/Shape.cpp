#include "Shape.h"
#include "../ColorManager.h"

namespace XWindowPlayground
{
    void Shape::Init(Display* display, Window* window)
    {
        if (!m_isInitialized)
        {
            Drawable::Init(display, window);
            m_graphicsContext = XCreateGC(display, *window, 0, 0);

            if (m_initColorOnInit)
            {
                InitColor();
            }
        }
    }

    void Shape::InitColor()
    {
        ColorManager* colorManager = ColorManager::GetColorManager(m_display);
        XColor xColor = colorManager->GetXColor(m_color);
        XSetForeground(m_display, m_graphicsContext, xColor.pixel);
        Draw();
    }

    void Shape::SetColor(Color color)
    {
        m_color = color;
        if (m_isInitialized)
        {
            InitColor();
        }
        else
        {
            m_initColorOnInit = true;           
        }
    }
}