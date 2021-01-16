#ifndef SHAPE_H
#define SHAPE_H

#include <X11/Xlib.h>
#include "../Drawable.h"
#include "../Color.h"

namespace XWindowPlayground {
    class Shape : public Drawable
    {
    private:
        bool m_initColorOnInit = false;

    protected:
        GC m_graphicsContext;
        Color m_color;

        bool m_fill;

    private:
        void InitColor();

    public:
        virtual ~Shape() {};

        virtual void Init(std::shared_ptr<Display> display, std::shared_ptr<Window> window) override;

        void SetColor(Color color);
        void Fill() { m_fill = true; }

        const GC& GetGC() const { return m_graphicsContext; }
    };
}

#endif