#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <unistd.h>
#include <iostream>

#include "Shapes/Shape.h"
#include "Shapes/Square.h"
#include "Shapes/Circle.h"
#include "Manager.h"

int main() {
    XWindowPlayground::Manager* manager = new XWindowPlayground::Manager{};
    manager->Initialize();

    XWindowPlayground::Shape* square = new XWindowPlayground::Square{0, 0, 100, 100};
    manager->AddShape(square);

    XWindowPlayground::Shape* circle = new XWindowPlayground::Circle{0, 0, 100, 100};
    manager->AddShape(circle);

    int returnCode = 0;
    while (returnCode == 0)
    {
        returnCode = manager->EventLoop();
    }

    delete manager;

    return returnCode;
}