#include "Clickable.h"

namespace XWindowLib
{
    void Clickable::DoClick(int button)
    {
        if (m_isHovering)
        {
            OnClick();
            switch (button)
            {
            case 1:
                m_isLeftClicking = true;
                OnLeftClick();
                break;
            case 2:
                m_isMiddleClicking = true;
                OnMiddleClick();
                break;
            case 3:
                m_isRightClicking = true;
                OnRightClick();
            default:
                break;
            }
        }
    }

    void Clickable::DoClickRelease(int button)
    {
        if (m_isLeftClicking && button == 1)
        {
            m_isLeftClicking = false;
            OnLeftClickRelease();
            OnClickRelease();
        }

        if (m_isMiddleClicking && button == 2)
        {
            m_isMiddleClicking = false;
            OnMiddleClickRelease();
            OnClickRelease();
        }

        if (m_isRightClicking && button == 3)
        {
            m_isRightClicking = false;
            OnRightClickRelease();
            OnClickRelease();
        }
    }
}