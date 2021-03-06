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
    textBox->SetBorderWidth(2);
    textBox->SetMargin(Margin{10});

    auto textBox2 = std::make_unique<TextBox>("2.");
    textBox2->SetBorderWidth(2);
    textBox2->SetMargin(Margin{10});

    auto textBox3 = std::make_unique<TextBox>("3.");
    textBox3->SetBorderWidth(2);
    textBox3->SetMargin(Margin{10});

    std::unique_ptr<StackContainer> container = std::make_unique<StackContainer>();
    container->SetPosition(Position{0, 10});
    container->SetDimensions(Dimensions{200, 200});
    container->SetDrawDirection(StackContainer::DrawDirection::LEFT_TO_RIGHT);
    container->SetOrientation(StackContainer::Orientation::HORIZONTAL);
    container->Add(std::move(textBox));
    container->Add(std::move(textBox2));
    container->Add(std::move(textBox3));
    manager->AddDrawable(std::move(container), "Container");

    auto buttonName = std::string("AlignmentButton");
    Dimensions buttonDimensions = Dimensions{100, 30};
    buttonDimensions.automatic = true;
    Button::Style style;
    style.borderRadius = 3;
    auto button = std::make_unique<Button>(style, Position{200, 50}, buttonDimensions, "Right To Left");
    button->SetColor(Color{65000, 0, 0});
    button->SetOnLeftClick([&manager](){
        StackContainer* container = dynamic_cast<StackContainer*>(manager->GetDrawable("Container").get());
        StackContainer::DrawDirection drawDirection = container->GetDrawDirection();
        StackContainer::Orientation orientation = container->GetOrientation();

        Button* button = dynamic_cast<Button*>(manager->GetDrawable("AlignmentButton").get());

        if (orientation == StackContainer::Orientation::HORIZONTAL)
        {
            if (drawDirection == StackContainer::DrawDirection::LEFT_TO_RIGHT)
            {
                button->SetText("Top To Bottom");
                container->SetDrawDirection(StackContainer::DrawDirection::RIGHT_TO_LEFT);
            }
            else
            {
                button->SetText("Bottom To Top");
                container->SetOrientation(StackContainer::Orientation::VERTICAL);
                container->SetDrawDirection(StackContainer::DrawDirection::TOP_TO_BOTTOM);
            }
        }
        else
        {
            if (drawDirection == StackContainer::DrawDirection::TOP_TO_BOTTOM)
            {
                button->SetText("Left To Right");
                container->SetDrawDirection(StackContainer::DrawDirection::BOTTOM_TO_TOP);
            }
            else
            {
                button->SetText("Right To Left");
                container->SetOrientation(StackContainer::Orientation::HORIZONTAL);
                container->SetDrawDirection(StackContainer::DrawDirection::LEFT_TO_RIGHT);
            }
        }
    });

    manager->AddDrawable(std::move(button), buttonName);
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