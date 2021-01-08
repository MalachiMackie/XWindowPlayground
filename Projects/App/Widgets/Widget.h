#ifndef WIDGET_H
#define WIDGET_H

#include <X11/Xlib.h>
#include <vector>
#include "../Shapes/Shape.h"
#include "../Drawable.h"

namespace XWindowPlayground
{
    class Widget : public Drawable
    {
    protected:
        std::vector<Shape*> m_shapes;

    public:
        virtual ~Widget();

        const std::vector<Shape*>& GetShapes() const { return m_shapes; }

        virtual void Draw() override;
        virtual void Init(Display* display, Window* window) override;
    };
}

#endif