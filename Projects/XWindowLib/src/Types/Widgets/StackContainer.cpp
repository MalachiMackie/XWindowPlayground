#include "StackContainer.h"

namespace XWindowLib
{
    void StackContainer::SetDrawDirection(DrawDirection drawDirection)
    {
        m_drawDirection = drawDirection;
        InitDrawables();
        Draw();
    }

    void StackContainer::InitDrawables()
    {
        for (int i = 0; i < m_drawables.size(); i++)
        {
            const auto& drawable = m_drawables[i];
            InitDrawable(drawable, i);
        }
    }

    void StackContainer::Add(std::unique_ptr<Drawable>&& drawable)
    {
        int index;
        AddDrawable(std::move(drawable), &index);
        if (m_isInitialized)
            InitDrawable(m_drawables[index], index);
    }

    void StackContainer::Init(std::shared_ptr<Display> display, std::shared_ptr<Window> window)
    {
        Widget::Init(display, window);
        InitDrawables();   
    }

    void StackContainer::InitDrawable(const std::unique_ptr<Drawable>& drawable, int index)
    {
        const auto& drawableMargin = drawable->GetMargin();
        const auto& drawableDimensions = drawable->GetDimensions();
        int x;
        int y = drawableMargin.top;
        switch (m_drawDirection)
        {
        default:
        case DrawDirection::LEFT_TO_RIGHT:
            x = drawable->GetMargin().left;
            break;
        case DrawDirection::RIGHT_TO_LEFT:
        {
            x = m_dimensions.width - drawableMargin.right - drawableDimensions.width;
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
                int newX = position.x + dimensions.width + margin.right;
                if (x < newX) x = newX + drawableMargin.left;
                break;
            }
            case DrawDirection::RIGHT_TO_LEFT:
                int newX = position.x - drawableDimensions.width - margin.left;
                if (x > newX) x = newX - drawableMargin.right;
                break;
            }
        }

        drawable->SetPosition(Position{x, y});
    }
}