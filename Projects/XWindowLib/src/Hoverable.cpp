#include "Hoverable.h"

namespace XWindowPlayground
{
    void Hoverable::CheckHovering(int mouseX, int mouseY)
    {
        bool isHovering = IsHovering(mouseX, mouseY);
        if (m_isHovering && !isHovering)
        {
            OnStopHover();
            m_isHovering = false;
        }
        else if (!m_isHovering && isHovering)
        {
            OnHover();
            m_isHovering = true;
        }
    }
}