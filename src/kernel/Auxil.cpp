#include "Auxil.h"
#include "logger.h"
#include <stdexcept>

RectangleArea::RectangleArea(Vector posVal, Vector sizeVal):
    pos(posVal), size(sizeVal){}

RectangleArea::RectangleArea(Vector sizeVal):
    pos(), size(sizeVal){}

RectangleArea::~RectangleArea(){}

const double EPS = 1e-8;
ProportionRatio::ProportionRatio(double val){
    operator=(val);
}

void ProportionRatio::operator=(double val){
    if(val > -EPS && val < 1 + EPS){
        val_ = val;
    }
    else{
        // TODO: to exception
        EDLOG("value: %g is out of range", val);
    }
}

ProportionRatio::operator double() const{ return val_; }

Vector::Vector(coord xc, coord yc):
    x(xc), y(yc){}

Vector::Vector():
    x(COORD_POISON), y(COORD_POISON){}

void Vector::operator+=(const Vector& other){
    this->x += other.x;
    this->y += other.y;

    return;
}

void Vector::operator-=(const Vector& other){
    this->x -= other.x;
    this->y -= other.y;

    return;
}

void Vector::operator*=(unsigned int ratio){
    this->x *= ratio;
    this->y *= ratio;

    return;
}

void Vector::operator/=(unsigned int ratio){
    this->x /= ratio;
    this->y /= ratio;

    return;
}

Vector operator+(const Vector& v1, const Vector& v2){
    Vector newObj(v1);
    newObj.operator+=(v2);

    return newObj;
}

Vector operator-(const Vector& v1, const Vector& v2){
    Vector newObj(v1);
    newObj.operator-=(v2);

    return newObj;
}

Vector operator*(const Vector& v1, unsigned int ratio){
    Vector newObj(v1);
    newObj.operator*=(ratio);

    return newObj;
}

Vector operator/(const Vector& v1, unsigned int ratio){
    Vector newObj(v1);
    newObj.operator/=(ratio);

    return newObj;
}

coord& Vector::operator[](unsigned int id){
    if(id > 1) throw std::out_of_range("");

    if(id == 0) return x;
    else return y;
}

Text::Text():
    font_size(12),
    str(),
    col(Color::BLACK)
{}

Text::Text(const std::string& text):
    font_size(12),
    str(text),
    col(Color::BLACK)
{}
