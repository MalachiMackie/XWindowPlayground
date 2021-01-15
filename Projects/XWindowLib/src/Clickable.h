#ifndef CLICKABLE_H
#define CLICKABLE_H

#include "Hoverable.h"

namespace XWindowPlayground
{
    class Clickable : public Hoverable
    {
    protected:
        virtual void OnClick(){};
        virtual void OnLeftClick(){};
        virtual void OnRightClick(){};
        virtual void OnMiddleClick(){};

    public:
        void DoClick(int button);
    };
}

#endif