#include "StackContainer.h"

namespace XWindowLib
{
    void StackContainer::SetDrawDirection(DrawDirection drawDirection)
    {
        m_drawDirection = drawDirection;
        InitDrawables();
    }

    void StackContainer::SetOrientation(Orientation orientation)
    {
        m_orientation = orientation;
        InitDrawables();
    }

    void StackContainer::InitDrawableHorizontal(const std::unique_ptr<Drawable>& drawable, int index)
    {
        const auto& drawableMargin = drawable->GetMargin();
        const auto& drawableDimensions = drawable->GetDimensions();
        int x;
        int y = m_position.y + drawableMargin.top;
        switch (m_drawDirection)
        {
        default:
        case DrawDirection::LEFT_TO_RIGHT:
            x = m_position.x + drawableMargin.left;
            break;
        case DrawDirection::RIGHT_TO_LEFT:
        {
            x = m_position.x + m_dimensions.width - drawableMargin.right - drawableDimensions.width;
            break;
        }
        }

        for(int i = 0; i < index; i++)
        {
            const auto& otherDrawable = m_drawables[i];
            if (otherDrawable == drawable)
                continue;

            const Margin& margin = otherDrawable->GetMargin();
            const Dimensions& dimensions = otherDrawable->GetDimensions();
            const Position& position = otherDrawable->GetPosition();

            switch (m_drawDirection)
            {
            default:
            case DrawDirection::LEFT_TO_RIGHT:
            {

                int newX = position.x + dimensions.width + margin.right + drawableMargin.left;
                if (x < newX)
                    x = newX;
                break;
            }
            case DrawDirection::RIGHT_TO_LEFT:
                int newX = position.x - margin.left - drawableMargin.right - drawableDimensions.width;
                if (x > newX)
                    x = newX;
                break;
            }
        }

        drawable->SetPosition(Position{x, y});
    }

    void StackContainer::InitDrawableVertical(const std::unique_ptr<Drawable>& drawable, int index)
    {
        const auto& drawableMargin = drawable->GetMargin();
        const auto& drawableDimensions = drawable->GetDimensions();
        int x = drawableMargin.left;
        int y;
        switch (m_drawDirection)
        {
        default:
        case DrawDirection::TOP_TO_BOTTOM:
            y = drawableMargin.top;
            break;
        
        case DrawDirection::BOTTOM_TO_TOP:
            y = m_dimensions.height - drawableMargin.bottom - drawableDimensions.height;
            break;
        }

        for(int i = 0; i < index; i++)
        {
            const auto& otherDrawable = m_drawables[i];
            if (otherDrawable == drawable)
                continue;

            const Margin& margin = otherDrawable->GetMargin();
            const Dimensions& dimensions = otherDrawable->GetDimensions();
            const Position& position = otherDrawable->GetPosition();

            switch (m_drawDirection)
            {
            default:
            case DrawDirection::TOP_TO_BOTTOM:
            {
                int newY = position.y + dimensions.height + margin.bottom + drawableMargin.top;
                if (y < newY)
                    y = newY;
                break;
            }
            
            case DrawDirection::BOTTOM_TO_TOP:
            {
                int newY = position.y - margin.top - drawableDimensions.height - drawableMargin.bottom;
                if (y > newY)
                    y = newY;
                break;
            }
            }
            
        }

        drawable->SetPosition(Position{x, y});
    }

    void StackContainer::InitDrawable(const std::unique_ptr<Drawable>& drawable, int index)
    {
        switch (m_orientation)
        {
        default:
        case Orientation::HORIZONTAL:
            InitDrawableHorizontal(drawable, index);
            break;
        
        case Orientation::VERTICAL:
            InitDrawableVertical(drawable, index);
            break;
        }
    }
}