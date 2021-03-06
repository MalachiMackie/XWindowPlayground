#include "Container.h"

namespace XWindowLib
{
    void Container::Add(std::unique_ptr<Drawable>&& drawable)
    {
        int index;
        AddDrawable(std::move(drawable), &index);
        if (m_isInitialized)
        {
            InitDrawable(m_drawables[index], index);
            Draw();
        }
    }

    void Container::InitDrawables()
    {
        for (int i = 0; i < m_drawables.size(); i++)
        {
            const auto& drawable = m_drawables[i];
            InitDrawable(drawable, i);
        }
        Draw();
    }

    void Container::Init(std::shared_ptr<Display> display, std::shared_ptr<Window> window)
    {
        Widget::Init(display, window);
        InitDrawables();   
    }
}