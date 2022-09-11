#include "drawer.h"
#include <assert.h>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include <math.h>

static const double EPS = 1e-8;

static const uint   LEN_ARROW_LINE_RATIO = 14;

static const sf::Color VECTOR_COLOR = sf::Color(200, 0, 0, 200);

void draw_line(sf::RenderWindow* window, CoordinateSus* ct_sus, double x_from, double y_from, double x_to, double y_to){

    assert(window != NULL);
    assert(ct_sus != NULL);

    int pix_from_x_ct = ct_sus->CountPixelPosX(x_from);
    int pix_from_y_ct = ct_sus->CountPixelPosY(y_from);
    int pix_to_x_ct   = ct_sus->CountPixelPosX(x_to);
    int pix_to_y_ct   = ct_sus->CountPixelPosY(y_to);

    if(pix_from_x_ct < ct_sus->x_lower_pixel() || pix_from_x_ct > ct_sus->x_upper_pixel()) return;
    if(pix_from_y_ct < ct_sus->y_upper_pixel() || pix_from_y_ct > ct_sus->y_lower_pixel()) return;
    if(pix_to_x_ct   < ct_sus->x_lower_pixel() || pix_to_x_ct   > ct_sus->x_upper_pixel()) return;
    if(pix_to_y_ct   < ct_sus->y_upper_pixel() || pix_to_y_ct   > ct_sus->y_lower_pixel()) return;

    sf::Vertex line_to_draw[] = {
        sf::Vertex(sf::Vector2f(pix_from_x_ct, pix_from_y_ct), VECTOR_COLOR),
        sf::Vertex(sf::Vector2f(pix_to_x_ct,   pix_to_y_ct), VECTOR_COLOR)
    };

    window->draw(line_to_draw, 2, sf::Lines);

    return;
}
//----------------------------------------------------------------------------------------//

// TODO: ISNULLDOUBLE FUNC
Vector::Vector(double v1, double v2, VT_DATA data_type){
    
    if(data_type == VT_DATA::COORD){

        assert(fabs(v1) > EPS || fabs(v2) > EPS);
    
        // TODO: x = y = 0 случай 
        x_ = v1;
        y_ = v2;

        if(fabs(x_) < EPS){
            if(y_ >= EPS){
                angle_ = M_PI / 2;
            }
            else{
                angle_ = (3 * M_PI) / 2;
            }
        }
        else{
            // TODO: check
            angle_ = atan(y_ / x_);

            if(x_ < -EPS){
                angle_ += M_PI;
            }
        }

        // TODO: sqrt needed??

        len_ = sqrt(fabs(x_ * x_ + y_ * y_));
    }
    else if(data_type == VT_DATA::POLAR){
        
        assert(v1 > EPS);
        len_   = v1;
        angle_ = v2;

        x_ = cos(angle_) * len_;
        y_ = sin(angle_) * len_;
    }
}
//----------------------------------------------------------------------------------------//

// TODO: ct == NULL case
Vector::Vector(Point* ct):
    x_(ct->x()), y_(ct->y())
{
    assert(fabs(x_) < EPS && fabs(y_) < EPS);
    
    if(fabs(x_) < EPS){
        if(y_ >= EPS){
            angle_ = M_PI / 2;
        }
        else{
            angle_ = (3 * M_PI) / 2;
        }
    }
    else{
        // TODO: check
        angle_ = atan(y_ / x_);
    }

    // TODO: sqrt needed??
    len_ = sqrt(fabs(x_ * y_));
}
//----------------------------------------------------------------------------------------//

// TODO: draw - внешняя ф-ция???

void Vector::Draw(sf::RenderWindow* window, CoordinateSus* ct_sus, double x_init, double y_init){
    
    assert(window != NULL);
    assert(ct_sus != NULL);

    double x_final_ct = x_init + x_;
    double y_final_ct = y_init + y_;
    
    draw_line(window, ct_sus, x_init, y_init, x_final_ct, y_final_ct);
    
    // TODO: refactor
    Vector arrow_line = this->NormalVector();
    arrow_line.ChangeLen(this->len() / (double)LEN_ARROW_LINE_RATIO);
    arrow_line = arrow_line - (*this / (double)LEN_ARROW_LINE_RATIO);
    
    draw_line(window, ct_sus, x_final_ct, y_final_ct, x_final_ct + arrow_line.x(), y_final_ct + arrow_line.y());

    arrow_line = -this->NormalVector();
    arrow_line.ChangeLen(this->len() / (double)LEN_ARROW_LINE_RATIO);
    arrow_line = arrow_line - (*this / (double)LEN_ARROW_LINE_RATIO);
    
    draw_line(window, ct_sus, x_final_ct, y_final_ct, x_final_ct + arrow_line.x(), y_final_ct + arrow_line.y());

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

Vector Vector::NormalVector(){

    return Vector(1, angle_ + M_PI / 2, VT_DATA::POLAR);
}
//----------------------------------------------------------------------------------------//

void Vector::Normalize(){

    x_   /= len_;
    y_   /= len_;
    len_  = 1;

    return;
}
//----------------------------------------------------------------------------------------//

void Vector::ChangeLen(double len_val){

    assert(len_val > EPS);

    x_  *= len_val / len_;
    y_  *= len_val / len_;
    len_ = len_val;

    return;
}
//----------------------------------------------------------------------------------------//

Vector Vector::operator +(const Vector &v2){

    return Vector(x_ + v2.x(), y_ + v2.y(), VT_DATA::COORD);
}
//----------------------------------------------------------------------------------------//

Vector Vector::operator -(const Vector &v2){

    return Vector(x_ - v2.x(), y_ - v2.y(), VT_DATA::COORD);
}
//----------------------------------------------------------------------------------------//

Vector Vector::operator *(double ratio){

    return Vector(len_ * ratio, angle_, VT_DATA::POLAR);
}
//----------------------------------------------------------------------------------------//

Vector Vector::operator /(double ratio){

    return Vector(len_ / ratio, angle_, VT_DATA::POLAR);
}
//----------------------------------------------------------------------------------------//

Vector Vector::operator -(){

    return Vector(-x_, -y_, VT_DATA::COORD);
}
//----------------------------------------------------------------------------------------//
