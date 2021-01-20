#ifndef CLICKABLE_H
#define CLICKABLE_H

#include "Hoverable.h"

namespace XWindowLib
{
    class Clickable : public Hoverable
    {
    private:
        bool m_isLeftClicking;
        bool m_isRightClicking;
        bool m_isMiddleClicking;

    protected:
        virtual void OnClick(){};
        virtual void OnLeftClick(){};
        virtual void OnRightClick(){};
        virtual void OnMiddleClick(){};

        virtual void OnClickRelease(){};
        virtual void OnLeftClickRelease(){};
        virtual void OnRightClickRelease(){};
        virtual void OnMiddleClickRelease(){};

        bool IsClicking() { return m_isLeftClicking || m_isRightClicking || m_isMiddleClicking; }

    public:
        void DoClick(int button);
        void DoClickRelease(int button);
    };
}

#endif