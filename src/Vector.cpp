#include "drawer.h"
#include <assert.h>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Vertex.hpp>

    Vector(double x, double y);
    Vector(Point* ct);
    
Vector::Vector(double x_offset, double y_offset, double x_init_ct, double y_init_ct):
    ct_init_(x_init_ct, y_init_ct),
    x_offset_(x_offset),
    y_offset_(y_offset)
{}
//----------------------------------------------------------------------------------------//

Vector::Vector(double x_offset, double y_offset, Point ct):
    ct_init_(ct),
    x_offset_(x_offset),
    y_offset_(y_offset)
{}
//----------------------------------------------------------------------------------------//

Vector::Vector(double x_offset, double y_offset, Vector* vt_from):
    ct_init_(vt_from->GetFinalPoint()),
    x_offset_(x_offset),
    y_offset_(y_offset)
{}
//----------------------------------------------------------------------------------------//

/*
Point Vector::GetFinalPoint(){

    return Point(ct_init_.GetX() + x_offset_, ct_init_.GetY() + y_offset_);
}
//----------------------------------------------------------------------------------------//
*/
void Vector::Draw(sf::RenderWindow* window, CoordinateSus* ct_sus){

    assert(window != NULL);
    assert(ct_sus != NULL);

    Point end_point(this->GetFinalPoint());

    int pix_from_x_ct = ct_sus->CountPixelPosX(ct_init_);
    int pix_from_y_ct = ct_sus->CountPixelPosY(ct_init_);
    int pix_to_x_ct   = ct_sus->CountPixelPosX(end_point);
    int pix_to_y_ct   = ct_sus->CountPixelPosY(end_point);

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
