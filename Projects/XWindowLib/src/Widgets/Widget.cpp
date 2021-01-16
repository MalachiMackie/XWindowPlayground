#include "Widget.h"

namespace XWindowPlayground
{
    void Widget::Draw()
    {
        for (auto &&shape : m_shapes)
        {
            shape->Draw();
        }
    }

    void Widget::Init(std::shared_ptr<Display> display, std::shared_ptr<Window> window)
    {
        if (!m_isInitialized)
        {
            Drawable::Init(display, window);
            for(auto &&shape : m_shapes)
            {
                Drawable* drawable = dynamic_cast<Drawable*>(shape.get());
                drawable->Init(display, window);
            }
        }
    }
}