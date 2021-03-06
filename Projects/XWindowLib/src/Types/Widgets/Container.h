#ifndef CONTAINER_H
#define CONTAINER_H

#include <vector>

#include "Types/Widgets/Widget.h"
#include "Types/Drawable.h"

namespace XWindowLib
{
    class Container : public Widget
    {

    protected:
        virtual void InitDrawable(const std::unique_ptr<Drawable>& drawable, int index) = 0;

    public:
        virtual void InitDrawables();

        void Add(std::unique_ptr<Drawable>&& drawable);

        virtual void Init(std::shared_ptr<Display> display, std::shared_ptr<Window> window) override;
        
    };
}

#endif