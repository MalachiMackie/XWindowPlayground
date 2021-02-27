#ifndef CONTAINER_H
#define CONTAINER_H

#include <vector>

#include "Types/Widgets/Widget.h"
#include "Types/Drawable.h"

namespace XWindowLib
{
    class StackContainer : public Widget
    {
    public:

        enum class DrawDirection
        {
            LEFT_TO_RIGHT,
            RIGHT_TO_LEFT
        };

    private:
        DrawDirection m_drawDirection = DrawDirection::LEFT_TO_RIGHT;

        void InitDrawable(const std::unique_ptr<Drawable>& drawable, int index);

    public:
        StackContainer(){};

        void InitDrawables();

        void Add(std::unique_ptr<Drawable>&& drawable);

        virtual void Init(std::shared_ptr<Display> display, std::shared_ptr<Window> window) override;

        void SetDrawDirection(DrawDirection drawDirection);
        const DrawDirection& GetDrawDirection() { return m_drawDirection; }
        
    };
}

#endif