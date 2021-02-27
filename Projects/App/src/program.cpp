#include <iostream>
#include <functional>
#include <memory>
#include <string>

#include <XWindowLib.h>

using namespace XWindowLib;

void ButtonsWithMovableText(const std::unique_ptr<Manager>& manager)
{
    Button::Style hoverStyle;
    hoverStyle.color = {0, 65000, 0};

    Button::Style clickStyle;
    clickStyle.color = {0, 0, 65000};

    Button::Style style;
    style.borderRadius = 5;
    style.color = {65000, 0, 0};
    auto movingButton = std::make_unique<Button>(style, Position{120, 10}, Dimensions{100, 100}, "Hello");
    movingButton->SetHoverStyle(hoverStyle);
    movingButton->SetClickStyle(clickStyle);

    Button::Style buttonStyle;
    buttonStyle.borderRadius = 5;
    buttonStyle.color = {0, 65000, 0};
    auto button1 = std::make_unique<Button>(buttonStyle, Position{10, 50}, Dimensions{100, 30}, "Vertical");
    button1->SetOnLeftClick([&manager](){
        Button* button = dynamic_cast<Button*>(manager->GetDrawable("movingButton").get());
        VerticalAlignment buttonVerticalAlignment;
        if (!button || !button->TryGetTextVerticalAlignment(&buttonVerticalAlignment))
        {
            return;
        }
        switch(buttonVerticalAlignment)
        {
            default:
            case VerticalAlignment::TOP:
                button->SetTextVerticalAlignment(VerticalAlignment::MIDDLE);
                break;
            case VerticalAlignment::MIDDLE:
                button->SetTextVerticalAlignment(VerticalAlignment::BOTTOM);
                break;
            case VerticalAlignment::BOTTOM:
                button->SetTextVerticalAlignment(VerticalAlignment::TOP);
                break;
        }
    });

    auto button2 = std::make_unique<Button>(buttonStyle, Position{10, 10}, Dimensions{100, 30}, "Horizontal");
    button2->SetOnLeftClick([& manager](){
        Button* button = dynamic_cast<Button*>(manager->GetDrawable("movingButton").get());
        TextAlignment buttonTextAlignment;
        if (!button || !button->TryGetTextAlignment(&buttonTextAlignment))
        {
            return;
        }
        switch (buttonTextAlignment)
        {
        default:
        case TextAlignment::LEFT:
            button->SetTextAlignment(TextAlignment::CENTER);
            break;
        case TextAlignment::CENTER:
            button->SetTextAlignment(TextAlignment::RIGHT);
            break;
        case TextAlignment::RIGHT:
            button->SetTextAlignment(TextAlignment::LEFT);
            break;
        }
    });

    manager->AddDrawable(std::move(button1));
    manager->AddDrawable(std::move(button2));
    manager->AddDrawable(std::move(movingButton), "movingButton");
}

void HorizontalContainer(const std::unique_ptr<Manager>& manager)
{
    auto textBox = std::make_unique<TextBox>("1.");
    textBox->SetMargin(Margin{10});

    auto textBox2 = std::make_unique<TextBox>("2.");
    textBox2->SetMargin(Margin{10});

    auto textBox3 = std::make_unique<TextBox>("3.");
    textBox3->SetMargin(Margin{10});

    std::unique_ptr<StackContainer> container = std::make_unique<StackContainer>();
    container->SetDimensions(Dimensions{600, 20});
    container->SetDrawDirection(StackContainer::DrawDirection::RIGHT_TO_LEFT);
    container->Add(std::move(textBox));
    container->Add(std::move(textBox2));
    container->Add(std::move(textBox3));
    manager->AddDrawable(std::move(container), "Container");
    dynamic_cast<StackContainer*>(manager->GetDrawable("Container").get())->InitDrawables();

    auto button = std::make_unique<Button>(Position{10, 50}, Dimensions{100, 30});
    button->SetOnLeftClick([&manager](){
        StackContainer* container = dynamic_cast<StackContainer*>(manager->GetDrawable("Container").get());
        StackContainer::DrawDirection drawDirection = container->GetDrawDirection();
        switch (drawDirection)
        {
        default:
        case StackContainer::DrawDirection::LEFT_TO_RIGHT:
        {
            container->SetDrawDirection(StackContainer::DrawDirection::RIGHT_TO_LEFT);
            break;
        }
        
        case StackContainer::DrawDirection::RIGHT_TO_LEFT:
        {
            container->SetDrawDirection(StackContainer::DrawDirection::LEFT_TO_RIGHT);
            break;
        }
        }
    });

    manager->AddDrawable(std::move(button));
}

int main() {
    std::unique_ptr<Manager> manager = std::make_unique<Manager>(1280, 720);
    manager->Initialize();

    // ButtonsWithMovableText(manager);
    HorizontalContainer(manager);

    int returnCode = 0;
    while (returnCode == 0)
    {
        returnCode = manager->EventLoop();
    }

    return returnCode;
}