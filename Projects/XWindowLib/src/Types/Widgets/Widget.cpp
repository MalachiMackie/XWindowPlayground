#include "Widget.h"

namespace XWindowLib
{
    void Widget::Draw()
    {
        for (auto &&drawable : m_drawables)
        {
            drawable->Draw();
        }
        Drawable::Draw();
    }

    void Widget::AddDrawable(std::unique_ptr<Drawable>&& drawable, int* index)
    {
        *index = m_drawables.size();
        m_drawables.push_back(std::move(drawable));
    }

    void Widget::Init(std::shared_ptr<Display> display, std::shared_ptr<Window> window)
    {
        if (!m_isInitialized)
        {
            Drawable::Init(display, window);
            for(auto &&drawable : m_drawables)
            {
                drawable->Init(display, window);
            }
        }
    }
}