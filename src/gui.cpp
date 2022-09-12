#include "gui.h"
#include <assert.h>

void DrawLine(sf::RenderWindow* window, double x1, double y1, double x2, double y2, sf::Color col){

    assert(window != NULL);

    sf::Vertex line_to_draw[] = {
        sf::Vertex(sf::Vector2f(x1, y1), col),
        sf::Vertex(sf::Vector2f(x2, y2), col)
    };

    window->draw(line_to_draw, 2, sf::Lines);

    return;
}
//----------------------------------------------------------------------------------------//
