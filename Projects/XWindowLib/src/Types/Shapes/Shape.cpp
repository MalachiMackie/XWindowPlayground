#include "Shape.h"

#include "Core/ColorManager.h"

namespace XWindowLib
{
    void Shape::Init(std::shared_ptr<Display> display, std::shared_ptr<Window> window)
    {
        if (!m_isInitialized)
        {
            Drawable::Init(display, window);

            XGCValues values;
            values.line_width = m_lineWidth;

            m_graphicsContext = XCreateGC(display.get(), *window, GCLineWidth, &values);

            if (m_initColorOnInit)
            {
                InitColor();
            }
        }
    }

    void Shape::InitColor()
    {
        std::shared_ptr<ColorManager> colorManager = ColorManager::GetColorManager(m_display);
        XColor xColor = colorManager->GetXColor(m_color);
        XSetForeground(m_display.get(), m_graphicsContext, xColor.pixel);
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