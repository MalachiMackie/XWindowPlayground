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
        if (!button)
        {
            return;
        }
        switch(button->GetTextVerticalAlignment())
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
        if (!button)
        {
            return;
        }
        switch (button->GetTextAlignment())
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

int main() {
    std::unique_ptr<Manager> manager = std::make_unique<Manager>(1280, 720);
    manager->Initialize();

    ButtonsWithMovableText(manager);

    int returnCode = 0;
    while (returnCode == 0)
    {
        returnCode = manager->EventLoop();
    }

    return returnCode;
}