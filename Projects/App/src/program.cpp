#include <iostream>
#include <functional>
#include <memory>

#include <XWindowLib.h>

using namespace XWindowPlayground;

int main() {
    Manager* manager = new Manager{1280, 720};
    manager->Initialize();

    Button::Style button1Style;
    button1Style.dimensions = {100, 100};
    button1Style.position = {50, 50};
    button1Style.color = {65000, 0, 0};
    button1Style.shadowDepth = 2;

    Button::Style button1HoverStyle{button1Style};
    button1HoverStyle.color = {0, 65000, 0};
    button1HoverStyle.shadowDepth = 0;

    auto button = std::make_unique<Button>(button1Style);
    button->SetHoverStyle(button1HoverStyle);
    button->SetOnLeftClick([](){
        std::cout << "Button One" << std::endl;
    });
    manager->AddDrawable(std::move(button));

    auto secondButton = std::make_unique<Button>(160, 50, 100, 35, 3);
    secondButton->SetColor(65000, 0, 0);
    secondButton->SetOnRightClick([](){
        std::cout << "Button Two" << std::endl;
    });
    manager->AddDrawable(std::move(secondButton));

    auto thirdButton = std::make_unique<Button>(270, 50, 100, 35, 0);
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