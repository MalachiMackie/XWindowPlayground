#ifndef WIDGET_H
#define WIDGET_H

#include <X11/Xlib.h>
#include <vector>
#include <memory>
#include "Types/Drawable.h"

namespace XWindowLib
{
    class Widget : public Drawable
    {
    protected:
        std::vector<std::unique_ptr<Drawable>> m_drawables;

    protected:
        void AddDrawable(std::unique_ptr<Drawable>&& drawable, int* index);

    public:
        virtual ~Widget() {};

        const std::vector<std::unique_ptr<Drawable>>& GetDrawables() const { return m_drawables; }

        virtual void Draw() override;
        virtual void Init(std::shared_ptr<Display> display, std::shared_ptr<Window> window) override;
    };
}

#endif