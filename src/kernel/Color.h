#ifndef COLOR_H
#define COLOR_H

#include <stdint.h>

// TODO: uint8_t to double for * operator
class Color{
public:
    Color(uint8_t r = 255, uint8_t g = 255, uint8_t b = 255, uint8_t a = 255);
    
    uint8_t r() const { return r_; }
    uint8_t g() const { return g_; }
    uint8_t b() const { return b_; }
    uint8_t a() const { return a_; }

    void    r(uint8_t v) { r_ = v; }
    void    g(uint8_t v) { g_ = v; }
    void    b(uint8_t v) { b_ = v; }
    void    a(uint8_t v) { a_ = v; }

    //operator double() const;

    void  operator +=(const Color& col2);
    void  operator *=(const Color& col2);
    void  operator *=(double ratio);
    void  operator -=(const Color& col2);

    Color operator +(const Color& col2) const;
    Color operator *(const Color& col2) const;
    Color operator *(double ratio) const;
    Color operator -(const Color& col2) const;

    // TODO: cast to uint32_t, cast from uint32_t, cast to const uint32_t&
private:
    uint8_t r_, g_, b_, a_;
};

static Color WHITE(255, 255, 255, 255);
static Color BLACK(  0,   0,   0, 255);
static Color RED(  255,   0,   0, 255);
static Color GREEN(  0, 255,   0, 255);
static Color BLUE(   0,   0, 255, 255);

#endif  // COLOR_H
