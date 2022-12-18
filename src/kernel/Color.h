#ifndef COLOR_H
#define COLOR_H

#include <stdint.h>

class Color{
public:
    Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255);
    Color(unsigned int val, uint8_t a = 255);

    uint8_t r() const { return r_; }
    uint8_t g() const { return g_; }
    uint8_t b() const { return b_; }
    uint8_t a() const { return a_; }

    void    r(uint8_t v) { r_ = v; }
    void    g(uint8_t v) { g_ = v; }
    void    b(uint8_t v) { b_ = v; }
    void    a(uint8_t v) { a_ = v; }

    unsigned int h() const;
    double       s() const;
    double       v() const;

    void h(unsigned int val);
    void s(double val);
    void v(double val);

    void hsv(unsigned int h, double s, double v);
    
    void  operator +=(const Color& col2);
    void  operator *=(const Color& col2);
    void  operator *=(double ratio);
    void  operator -=(const Color& col2);

    Color operator +(const Color& col2) const;
    Color operator *(const Color& col2) const;
    Color operator *(double ratio) const;
    Color operator -(const Color& col2) const;

    operator unsigned int() const;

    //!! implement?
    //explicit operator const uint32_t&() const;

    static Color WHITE;
    static Color BLACK;
    static Color RED;
    static Color GREEN;
    static Color BLUE;

private:
    uint8_t r_, g_, b_, a_;
};

uint32_t convertTosColor(const Color& col);
Color convertFromsColor(uint32_t val);

// TODO: struct palette

#endif  // COLOR_H
