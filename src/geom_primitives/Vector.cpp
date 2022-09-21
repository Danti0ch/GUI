#include "geometry_objects.h"
#include <assert.h>
#include <math.h>

using namespace geom;
Vector::Vector():
    x_(1), y_(1)
{}
//----------------------------------------------------------------------------------------//

Vector::Vector(double v1, double v2, VT_DATA mod){
    if(mod == VT_DATA::COORD){
        x_ = v1;
        y_ = v2;
    }
    else{
        x_ = cos(v2) * v1;
        y_ = sin(v2) * v1;
    }
}
//----------------------------------------------------------------------------------------//

Vector Vector::NormalVector(double len) const{

    double len_mod = len / this->len();

    return Vector(-y_ * len_mod, x_ * len_mod, VT_DATA::COORD);
}
//----------------------------------------------------------------------------------------//

void Vector::Normalize(){

    double cur_len = len();

    x_   /= cur_len;
    y_   /= cur_len;

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

    return;
}
//----------------------------------------------------------------------------------------//

double Vector::len() const {

    return sqrt(x_ * x_ + y_ * y_);
}
//----------------------------------------------------------------------------------------//

Vector Vector::operator +(const Vector &v2) const{

    Vector tmp = *this;
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

    return;
}
//----------------------------------------------------------------------------------------//

void Vector::operator -=(const Vector& v){

    x_ -= v.x();
    y_ -= v.y();

    return;
}
//----------------------------------------------------------------------------------------//

void Vector::operator *=(double ratio){

    x_   *= ratio;
    y_   *= ratio;

    return;
}
//----------------------------------------------------------------------------------------//

void Vector::operator /=(double ratio){

    x_ /= ratio;
    y_ /= ratio;

    return;
}
//----------------------------------------------------------------------------------------//
