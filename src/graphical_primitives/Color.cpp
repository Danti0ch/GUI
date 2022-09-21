#include "graphic_lib_wrapper.h"

using namespace gglib;

const uint MAX_COMP_VAL = 255;

Color::Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a):
    r_(r), g_(g), b_(b), a_(a){}

Color::Color(uint8_t r, uint8_t g, uint8_t b):
    r_(r), g_(g), b_(b), a_(255){}

void Color::operator +=(const Color& col2){

    r_ = (r_ > MAX_COMP_VAL - col2.r()) ? MAX_COMP_VAL : r_ + col2.r();
    g_ = (g_ > MAX_COMP_VAL - col2.g()) ? MAX_COMP_VAL : g_ + col2.g();
    b_ = (b_ > MAX_COMP_VAL - col2.b()) ? MAX_COMP_VAL : b_ + col2.b();
    a_ = (a_ > MAX_COMP_VAL - col2.a()) ? MAX_COMP_VAL : a_ + col2.a();
    
    return;
}
//----------------------------------------------------------------------------------------//

void Color::operator *=(const Color& col2){

    uint r_new = ((uint)r_ * (uint)col2.r()) / MAX_COMP_VAL;
    uint g_new = ((uint)g_ * (uint)col2.g()) / MAX_COMP_VAL;
    uint b_new = ((uint)b_ * (uint)col2.b()) / MAX_COMP_VAL;
    uint a_new = ((uint)a_ * (uint)col2.a()) / MAX_COMP_VAL;
    
    r_ = (r_new > MAX_COMP_VAL) ? MAX_COMP_VAL : r_new;
    g_ = (g_new > MAX_COMP_VAL) ? MAX_COMP_VAL : g_new;
    b_ = (b_new > MAX_COMP_VAL) ? MAX_COMP_VAL : b_new;
    a_ = (a_new > MAX_COMP_VAL) ? MAX_COMP_VAL : a_new;
    
    return;
}
//----------------------------------------------------------------------------------------//

void Color::operator *=(double ratio){

    uint r_new = (double)r_ * ratio;
    uint g_new = (double)g_ * ratio;
    uint b_new = (double)b_ * ratio;
    uint a_new = (double)a_ * ratio;
    
    r_ = (r_new > MAX_COMP_VAL) ? MAX_COMP_VAL : r_new;
    g_ = (g_new > MAX_COMP_VAL) ? MAX_COMP_VAL : g_new;
    b_ = (b_new > MAX_COMP_VAL) ? MAX_COMP_VAL : b_new;
    a_ = (a_new > MAX_COMP_VAL) ? MAX_COMP_VAL : a_new;

    return;
}
//----------------------------------------------------------------------------------------//

void Color::operator -=(const Color& col2){

    r_ = (r_ < col2.r()) ? 0 : r_ - col2.r();
    g_ = (g_ < col2.g()) ? 0 : g_ - col2.g();
    b_ = (b_ < col2.b()) ? 0 : b_ - col2.b();
    a_ = (a_ < col2.a()) ? 0 : a_ - col2.a();
    
    return;
}
//----------------------------------------------------------------------------------------//

Color Color::operator +(const Color& col2) const{

    Color new_obj = *this;
    new_obj.operator+=(col2);

    return new_obj;
}
//----------------------------------------------------------------------------------------//

Color Color::operator *(const Color& col2) const{

    Color new_obj = *this;
    new_obj.operator*=(col2);

    return new_obj;
}
//----------------------------------------------------------------------------------------//

Color Color::operator *(double ratio) const{

    Color new_obj = *this;
    new_obj.operator*=(ratio);

    return new_obj;
}
//----------------------------------------------------------------------------------------//

Color Color::operator -(const Color& col2) const{

    Color new_obj = *this;
    new_obj.operator-=(col2);

    return new_obj;
}
//----------------------------------------------------------------------------------------//
