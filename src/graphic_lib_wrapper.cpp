#include "graphic_lib_wrapper.h"
#include <assert.h>

Vertex VertexCtor(int x, int y, gl::Color col){

    return sf::Vertex(sf::Vector2f(x, y), col);
}
//----------------------------------------------------------------------------------------//
        window->draw(pixels, n_x_pixels * n_y_pixels, sf::Points);
window->getSize().y
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