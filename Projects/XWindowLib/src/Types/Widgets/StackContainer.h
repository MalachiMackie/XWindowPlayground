#ifndef STACK_CONTAINER_H
#define STACK_CONTAINER_H

#include <vector>

#include "Types/Widgets/Container.h"
#include "Types/Drawable.h"

namespace XWindowLib
{
    class StackContainer : public Container
    {
    public:

        enum class DrawDirection
        {
            LEFT_TO_RIGHT,
            RIGHT_TO_LEFT,
            TOP_TO_BOTTOM,
            BOTTOM_TO_TOP
        };
        enum class Orientation
        {
            HORIZONTAL,
            VERTICAL
        };

    private:
        DrawDirection m_drawDirection = DrawDirection::LEFT_TO_RIGHT;
        Orientation m_orientation = Orientation::HORIZONTAL;

    private:
        void InitDrawableHorizontal(const std::unique_ptr<Drawable>& drawable, int index);
        void InitDrawableVertical(const std::unique_ptr<Drawable>& drawable, int index);

    protected:

        virtual void InitDrawable(const std::unique_ptr<Drawable>& drawable, int index) override;

    public:
        void SetDrawDirection(DrawDirection drawDirection);
        const DrawDirection& GetDrawDirection() { return m_drawDirection; }

        void SetOrientation(Orientation orientation);
        const Orientation& GetOrientation() { return m_orientation; }
        
    };
}

#endif