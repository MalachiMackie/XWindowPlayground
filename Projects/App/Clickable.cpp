#include "Clickable.h"

namespace XWindowPlayground
{
    void Clickable::DoClick(int button)
    {
        if (m_isHovering)
        {
            OnClick();
            switch (button)
            {
            case 1:
                OnLeftClick();
                break;
            case 2:
                OnMiddleClick();
                break;
            case 3:
                OnRightClick();
            default:
                break;
            }
        }
    }
}