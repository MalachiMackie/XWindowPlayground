#ifndef HOVERABLE_H
#define HOVERABLE_H

namespace XWindowPlayground
{
    class Hoverable
    {
    protected:
        bool m_isHovering;

    protected:
        virtual void OnHover() = 0;
        virtual void OnStopHover() = 0;
        virtual bool IsHovering(int mouseX, int mouseY) = 0;

    public:
        void CheckHovering(int mouseX, int mouseY);
    };
}

#endif