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

    void Widget::Init(Display* display, Window* window)
    {
        if (!m_isInitialized)
        {
            Drawable::Init(display, window);
            for(auto &&shape : m_shapes)
            {
                Drawable* drawable = dynamic_cast<Drawable*>(shape);
                drawable->Init(display, window);
            }
        }
    }

    Widget::~Widget()
    {
        for(auto shape : m_shapes)
        {
            delete shape;
        }
    }
}