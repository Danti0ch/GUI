#include "drawer.h"
#include <assert.h>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Vertex.hpp>

Vector::Vector(double x, double y):
    x_(x), y_(y)
{}

Vector::Vector(Point* ct):
    x_(ct->x()), y_(ct->y())
{}

// TODO: draw - внешняя ф-ция???

void Vector::Draw(sf::RenderWindow* window, CoordinateSus* ct_sus, double x_init, double y_init){
    
    assert(window != NULL);
    assert(ct_sus != NULL);

    int pix_from_x_ct = ct_sus->CountPixelPosX(x_init);
    int pix_from_y_ct = ct_sus->CountPixelPosY(y_init);
    int pix_to_x_ct   = ct_sus->CountPixelPosX(this->x());
    int pix_to_y_ct   = ct_sus->CountPixelPosY(this->y());

    if(pix_from_x_ct < ct_sus->x_lower_pixel() || pix_from_x_ct > ct_sus->x_upper_pixel()) return;
    if(pix_from_y_ct < ct_sus->y_upper_pixel() || pix_from_y_ct > ct_sus->y_lower_pixel()) return;
    if(pix_to_x_ct   < ct_sus->x_lower_pixel() || pix_to_x_ct   > ct_sus->x_upper_pixel()) return;
    if(pix_to_y_ct   < ct_sus->y_upper_pixel() || pix_to_y_ct   > ct_sus->y_lower_pixel()) return;

    sf::Vertex line_to_draw[] = {
        sf::Vertex(sf::Vector2f(pix_from_x_ct, pix_from_y_ct)),
        sf::Vertex(sf::Vector2f(pix_to_x_ct,   pix_to_y_ct))
    };
    
    window->draw(line_to_draw, 2, sf::Lines);

    return;
}
//----------------------------------------------------------------------------------------//

void Vector::Draw(sf::RenderWindow* window, CoordinateSus* ct_sus){

    assert(window != NULL);
    assert(ct_sus != NULL);

    Draw(window, ct_sus, 0, 0);
    return;
}
//----------------------------------------------------------------------------------------//

void Vector::Draw(sf::RenderWindow* window, CoordinateSus* ct_sus, Point* ct_init){

    assert(window  != NULL);
    assert(ct_sus  != NULL);
    assert(ct_init != NULL);

    Draw(window, ct_sus, ct_init->x(), ct_init->y());
    return;
}
//----------------------------------------------------------------------------------------//

void Vector::Draw(sf::RenderWindow* window, CoordinateSus* ct_sus, Vector* vt_init){

    assert(window  != NULL);
    assert(ct_sus  != NULL);
    assert(vt_init != NULL);

    Draw(window, ct_sus, vt_init->x(), vt_init->y());
    return;
}
//----------------------------------------------------------------------------------------//
