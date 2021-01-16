#ifndef WIDGET_H
#define WIDGET_H

#include <X11/Xlib.h>
#include <vector>
#include <memory>
#include "../Shapes/Shape.h"
#include "../Drawable.h"

namespace XWindowPlayground
{
    class Widget : public Drawable
    {
    protected:
        std::vector<std::unique_ptr<Shape>> m_shapes;

    public:
        virtual ~Widget() {};

        const std::vector<std::unique_ptr<Shape>>& GetShapes() const { return m_shapes; }

        virtual void Draw() override;
        virtual void Init(std::shared_ptr<Display> display, std::shared_ptr<Window> window) override;
    };
}

#endif