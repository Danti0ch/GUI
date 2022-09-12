#include "drawable_objects.h"
#include "gui.h"
#include <assert.h>
#include <math.h>

static const double EPS = 1e-8;
static const uint   LEN_ARROW_LINE_RATIO = 14;

static const sf::Color VECTOR_COLOR = sf::Color(200, 0, 0, 200);

static void draw_real_line(sf::RenderWindow* window, const CoordinateSus& ct_sus, double x_from, double y_from, double x_to, double y_to, const sf::Color& col){

    assert(window != NULL);

    int pix_from_x_ct = ct_sus.CountPixelPosX(x_from);
    int pix_from_y_ct = ct_sus.CountPixelPosY(y_from);
    int pix_to_x_ct   = ct_sus.CountPixelPosX(x_to);
    int pix_to_y_ct   = ct_sus.CountPixelPosY(y_to);

    if(pix_from_x_ct < ct_sus.x_lower_pixel() || pix_from_x_ct > ct_sus.x_upper_pixel()) return;
    if(pix_from_y_ct < ct_sus.y_upper_pixel() || pix_from_y_ct > ct_sus.y_lower_pixel()) return;
    if(pix_to_x_ct   < ct_sus.x_lower_pixel() || pix_to_x_ct   > ct_sus.x_upper_pixel()) return;
    if(pix_to_y_ct   < ct_sus.y_upper_pixel() || pix_to_y_ct   > ct_sus.y_lower_pixel()) return;

    DrawLine(window, pix_from_x_ct, pix_from_y_ct, pix_to_x_ct, pix_to_y_ct, col);

    return;
}
//----------------------------------------------------------------------------------------//

Vector::Vector():
    x_(1), y_(1)
{
    angle_ = atan(y_ / x_);
    len_   = sqrt(x_ * x_ + y_ * y_);
}
//----------------------------------------------------------------------------------------//

Vector::Vector(double v1, double v2, VT_DATA data_type){
    
    if(data_type == VT_DATA::COORD){

        // TODO: check
        /*
        if(fabs(v1) < EPS && fabs(v2) < EPS){
            x_ = 0;
            y_ = 0;

            angle_ = M_PI / 2;
            len_   = 0;
        }
        */
        
        x_ = v1;
        y_ = v2;

        if(fabs(x_) < EPS){
            if(y_ >= EPS) angle_ = M_PI / 2;
            else          angle_ = (3 * M_PI) / 2;
        }
        else{
            angle_ = atan(y_ / x_);

            if(x_ < -EPS) angle_ += M_PI;
        }
        len_ = sqrt(fabs(x_ * x_ + y_ * y_));
    
    }
    else if(data_type == VT_DATA::POLAR){

/*        if(v1 < EPS){
            len_   = 0;
            angle_ = M_PI / 2;
            x_     = 0;
            y_     = 0;
        }*/
        
        len_   = v1;
        angle_ = v2;

        x_ = cos(angle_) * len_;
        y_ = sin(angle_) * len_;
    
    }
}
//----------------------------------------------------------------------------------------//

// TODO: draw внешней функцией?
void Vector::Draw(sf::RenderWindow* window, const CoordinateSus& ct_sus, double x_init, double y_init, sf::Color col) const {
    
    assert(window != NULL);

    double x_final_ct = x_init + x_;
    double y_final_ct = y_init + y_;
    
    draw_real_line(window, ct_sus, x_init, y_init, x_final_ct, y_final_ct, col);
    
    Vector arrow_line = this->NormalVector(len() / (double)LEN_ARROW_LINE_RATIO);
    arrow_line = arrow_line - (*this / (double)LEN_ARROW_LINE_RATIO);
    
    draw_real_line(window, ct_sus, x_final_ct, y_final_ct, x_final_ct + arrow_line.x(), y_final_ct + arrow_line.y(), col);

    arrow_line = -this->NormalVector(len() / (double)LEN_ARROW_LINE_RATIO);
    arrow_line = arrow_line - (*this / (double)LEN_ARROW_LINE_RATIO);
    
    draw_real_line(window, ct_sus, x_final_ct, y_final_ct, x_final_ct + arrow_line.x(), y_final_ct + arrow_line.y(), col);

    return;
}
//----------------------------------------------------------------------------------------//

void Vector::Draw(sf::RenderWindow* window, const CoordinateSus& ct_sus, sf::Color col) const {

    assert(window != NULL);

    Draw(window, ct_sus, 0, 0, col);
    return;
}
//----------------------------------------------------------------------------------------//

void Vector::Draw(sf::RenderWindow* window, const CoordinateSus& ct_sus, const Vector& vt_init, sf::Color col) const {

    assert(window  != NULL);

    Draw(window, ct_sus, vt_init.x(), vt_init.y(), col);
    return;
}
//----------------------------------------------------------------------------------------//

Vector Vector::NormalVector(double len) const {

    return Vector(len, angle_ + M_PI / 2, VT_DATA::POLAR);
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

Vector Vector::operator +(const Vector &v2) const {

    return Vector(x_ + v2.x(), y_ + v2.y(), VT_DATA::COORD);
}
//----------------------------------------------------------------------------------------//

Vector Vector::operator -(const Vector &v2) const {

    return Vector(x_ - v2.x(), y_ - v2.y(), VT_DATA::COORD);
}
//----------------------------------------------------------------------------------------//

Vector Vector::operator *(double ratio) const {

    return Vector(len_ * ratio, angle_, VT_DATA::POLAR);
}
//----------------------------------------------------------------------------------------//

Vector Vector::operator /(double ratio) const {

    return Vector(len_ / ratio, angle_, VT_DATA::POLAR);
}
//----------------------------------------------------------------------------------------//

Vector Vector::operator -() const {

    return Vector(-x_, -y_, VT_DATA::COORD);
}
//----------------------------------------------------------------------------------------//
