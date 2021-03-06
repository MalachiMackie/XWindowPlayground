#ifndef SHAPE_H
#define SHAPE_H

#include <X11/Xlib.h>
#include "Types/Drawable.h"
#include "Types/IHaveColor.h"
#include "Core/Color.h"

namespace XWindowLib {
    class Shape : public Drawable, public IHaveColor
    {
    private:
        bool m_initColorOnInit = false;

    protected:
        GC m_graphicsContext;

        bool m_fill = false;
        int m_lineWidth = 0;

    private:
        void InitColor();

    public:
        virtual ~Shape() {};

        virtual void Init(std::shared_ptr<Display> display, std::shared_ptr<Window> window) override;

        virtual void SetColor(Color color) override;
        void Fill() { m_fill = true; }

        const GC& GetGC() const { return m_graphicsContext; }
    };
}

#endif