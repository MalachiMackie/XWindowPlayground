#include <iostream>
#include <functional>

#include <XWindowLib.h>

using namespace XWindowPlayground;

int main() {
    Manager* manager = new Manager{1280, 720};
    manager->Initialize();

    Button* button = new Button{50, 50, 100, 100, 5};
    button->SetColor(65000, 0, 0);
    button->SetOnLeftClick([](){
        std::cout << "Button One" << std::endl;
    });
    manager->AddDrawable(button);

    Button* secondButton = new Button{160, 50, 100, 35, 3};
    secondButton->SetColor(65000, 0, 0);
    secondButton->SetOnRightClick([](){
        std::cout << "Button Two" << std::endl;
    });
    manager->AddDrawable(secondButton);


    // XWindowPlayground::Shape* circle = new XWindowPlayground::Circle{0, 0, 100, 100};
    // circle->Fill();
    // manager->AddDrawable(circle);

    int returnCode = 0;
    while (returnCode == 0)
    {
        returnCode = manager->EventLoop();
    }

    delete manager;

    return returnCode;
}