#include <iostream>
#include <functional>
#include <memory>

#include <XWindowLib.h>

using namespace XWindowLib;

int main() {
    Manager* manager = new Manager{1280, 720};
    manager->Initialize();

    Button::Style button1Style;
    button1Style.dimensions = {100, 100};
    button1Style.position = {50, 50};
    button1Style.color = {65000, 0, 0};
    button1Style.borderRadius = 20;

    Button::Style button1HoverStyle{button1Style};
    button1HoverStyle.color = {0, 65000, 0};

    Button::Style button1ClickStyle{button1Style};
    button1ClickStyle.color = {0, 0, 65000};

    auto button = std::make_unique<Button>(button1Style);
    button->SetHoverStyle(button1HoverStyle);
    button->SetClickStyle(button1ClickStyle);
    button->SetOnLeftClick([](){
        std::cout << "Button One" << std::endl;
    });
    manager->AddDrawable(std::move(button));

    Button::Style button2HoverStyle;
    button2HoverStyle.color = {0, 65000, 0};

    auto secondButton = std::make_unique<Button>(160, 50, 100, 35);
    secondButton->SetHoverStyle(button2HoverStyle);
    secondButton->SetColor(65000, 0, 0);
    secondButton->SetOnRightClick([](){
        std::cout << "Button Two" << std::endl;
    });
    manager->AddDrawable(std::move(secondButton));

    auto thirdButton = std::make_unique<Button>(270, 50, 100, 35);
    thirdButton->SetColor(65000, 0, 0);
    manager->AddDrawable(std::move(thirdButton));

    int returnCode = 0;
    while (returnCode == 0)
    {
        returnCode = manager->EventLoop();
    }

    delete manager;

    return returnCode;
}