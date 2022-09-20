#include "drawable_objects.h"
#include <assert.h>
#include <math.h>

static const double EPS                  = 1e-8;
static const uint   LEN_ARROW_LINE_RATIO = 14;

static const Color VECTOR_COLOR = Color(200, 0, 0, 200);

static void draw_real_line(GraphicSpace* editor, const CoordinateSus& ct_sus, double x_from, double y_from, double x_to, double y_to, Color col){

    assert(editor != NULL);

    int pix_from_x_ct = ct_sus.CountPixelPosX(x_from);
    int pix_from_y_ct = ct_sus.CountPixelPosY(y_from);
    int pix_to_x_ct   = ct_sus.CountPixelPosX(x_to);
    int pix_to_y_ct   = ct_sus.CountPixelPosY(y_to);

    if(pix_from_x_ct < ct_sus.x_lower_pixel() || pix_from_x_ct > ct_sus.x_upper_pixel()) return;
    if(pix_from_y_ct < ct_sus.y_upper_pixel() || pix_from_y_ct > ct_sus.y_lower_pixel()) return;
    if(pix_to_x_ct   < ct_sus.x_lower_pixel() || pix_to_x_ct   > ct_sus.x_upper_pixel()) return;
    if(pix_to_y_ct   < ct_sus.y_upper_pixel() || pix_to_y_ct   > ct_sus.y_lower_pixel()) return;

    editor->DrawLine(pix_from_x_ct, pix_from_y_ct, pix_to_x_ct, pix_to_y_ct, col);

    return;
}
//----------------------------------------------------------------------------------------//

Vector::Vector():
    x_(1), y_(1),
    len_(NAN), angle_(NAN)
{}
//----------------------------------------------------------------------------------------//

Vector::Vector(double v1, double v2, VT_DATA mod){
    if(mod == VT_DATA::COORD){
        x_ = v1;
        y_ = v2;

        len_   = NAN;
        angle_ = NAN;
    }
    else{

        len_   = v1;
        angle_ = v2;

        x_ = cos(angle_) * len_;
        y_ = sin(angle_) * len_;
    }
}
//----------------------------------------------------------------------------------------//

void Vector::Draw(GraphicSpace* editor, const CoordinateSus& ct_sus, double x_init, double y_init, Color col){
    
    assert(editor != NULL);

    double x_final_ct = x_init + x_;
    double y_final_ct = y_init + y_;
    
    draw_real_line(editor, ct_sus, x_init, y_init, x_final_ct, y_final_ct, col);
    
    Vector arrow_line = this->NormalVector(this->len() / (double)LEN_ARROW_LINE_RATIO);
    
    // HERE MAN
    //arrow_line = arrow_line - (*this / (double)LEN_ARROW_LINE_RATIO);
    arrow_line -= (*this / (double)LEN_ARROW_LINE_RATIO);
    
    draw_real_line(editor, ct_sus, x_final_ct, y_final_ct, x_final_ct + arrow_line.x(), y_final_ct + arrow_line.y(), col);

    arrow_line = -this->NormalVector(this->len() / (double)LEN_ARROW_LINE_RATIO);
    arrow_line -= (*this / (double)LEN_ARROW_LINE_RATIO);
    
    draw_real_line(editor, ct_sus, x_final_ct, y_final_ct, x_final_ct + arrow_line.x(), y_final_ct + arrow_line.y(), col);

    return;
}
//----------------------------------------------------------------------------------------//

void Vector::Draw(GraphicSpace* editor, const CoordinateSus& ct_sus, Color col){

    assert(editor != NULL);

    Draw(editor, ct_sus, 0, 0, col);
    return;
}
//----------------------------------------------------------------------------------------//

void Vector::Draw(GraphicSpace* editor, const CoordinateSus& ct_sus, const Vector& vt_init, Color col){

    assert(editor  != NULL);

    Draw(editor, ct_sus, vt_init.x(), vt_init.y(), col);
    return;
}
//----------------------------------------------------------------------------------------//

Vector Vector::NormalVector(double len){

    double len_mod = len / this->len();

    return Vector(-y_ * len_mod, x_ * len_mod, VT_DATA::COORD);
}
//----------------------------------------------------------------------------------------//

void Vector::Normalize(){

    double cur_len = len();

    x_   /= cur_len;
    y_   /= cur_len;
    len_  = 1;

    return;
}
//----------------------------------------------------------------------------------------//

void Vector::ChangeLen(double len_val){

    assert(len_val > -EPS);

    if(len_val < EPS){
        x_ = 0; y_ = 0;
        return;
    }

    double len_mod = len_val / len();

    x_  *= len_mod;
    y_  *= len_mod;
    len_ = len_val;

    return;
}
//----------------------------------------------------------------------------------------//

double Vector::len(){

    if(std::isnan(len_)){
        len_ = sqrt(x_ * x_ + y_ * y_);
    }

    return len_;
}
//----------------------------------------------------------------------------------------//

Vector operator +(const Vector& v1, const Vector &v2){

    Vector tmp = v1;
    tmp += v2;
    
    return tmp;
}
//----------------------------------------------------------------------------------------//

Vector Vector::operator -(const Vector &v2) const {

    Vector tmp = *this;
    tmp -= v2;
    
    return tmp;
}
//----------------------------------------------------------------------------------------//

Vector Vector::operator *(double ratio) const {

    Vector tmp = *this;
    tmp *= ratio;
    
    return tmp;
}
//----------------------------------------------------------------------------------------//

Vector Vector::operator /(double ratio) const {

    Vector tmp = *this;
    tmp /= ratio;

    return tmp;
}
//----------------------------------------------------------------------------------------//

Vector Vector::operator -() const {

    return Vector(-x_, -y_, VT_DATA::COORD);
}
//----------------------------------------------------------------------------------------//

void Vector::operator +=(const Vector& v){

    x_ += v.x();
    y_ += v.y();
    len_ = NAN;

    return;
}
//----------------------------------------------------------------------------------------//

void Vector::operator -=(const Vector& v){

    x_ -= v.x();
    y_ -= v.y();
    len_ = NAN;

    return;
}
//----------------------------------------------------------------------------------------//

void Vector::operator *=(double ratio){

    x_   *= ratio;
    y_   *= ratio;
    len_ *= ratio;

    return;
}
//----------------------------------------------------------------------------------------//

void Vector::operator /=(double ratio){

    x_ /= ratio;
    y_ /= ratio;

    len_ /= ratio;

    return;
}
//----------------------------------------------------------------------------------------//
