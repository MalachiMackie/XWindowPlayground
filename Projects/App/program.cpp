#include "Shapes/Shape.h"
#include "Shapes/Square.h"
#include "Shapes/Circle.h"
#include "Manager.h"
#include "Color.h"

int main() {
    XWindowPlayground::Manager* manager = new XWindowPlayground::Manager{};
    manager->Initialize();

    XWindowPlayground::Shape* square = new XWindowPlayground::Square{0, 0, 100, 100};
    XWindowPlayground::Color squareFillColor;
    squareFillColor.Set(65000, 0, 0);
    square->SetColor(squareFillColor);
    square->Fill();
    manager->AddShape(square);

    XWindowPlayground::Shape* circle = new XWindowPlayground::Circle{0, 0, 100, 100};
    circle->Fill();
    manager->AddShape(circle);

    int returnCode = 0;
    while (returnCode == 0)
    {
        returnCode = manager->EventLoop();
    }

    delete manager;

    return returnCode;
}