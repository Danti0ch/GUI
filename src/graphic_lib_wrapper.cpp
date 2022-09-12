#include "graphic_lib_wrapper.h"

void WindowDrawLine(Window* window, double x1, double y1, double x2, double y2){

    assert(window != NULL);

    sf::Vertex line_to_draw[] = {
        sf::Vertex(sf::Vector2f(x1, y1)),
        sf::Vertex(sf::Vector2f(x2, y2))
    };

    window->draw(line_to_draw, 2, sf::Lines);

    return;
}
//----------------------------------------------------------------------------------------//