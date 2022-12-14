/**
 * @file Primitives.h
 * @brief auxil structures, functions and etc
 * @version 0.1
 * 
 */
#ifndef AUXIL_H
#define AUXIL_H

#include "Color.h"
#include <vector>
#include <string>

typedef unsigned int coord;
const coord COORD_POISON = -1;

enum class ORIENTATION{
    H, V
};

class Vector{
public:
    Vector();
    Vector(coord x, coord y);

    void operator+=(const Vector& other);
    void operator-=(const Vector& other);

    coord& operator[](unsigned int id);
    
    coord x, y;
};

Vector operator+(const Vector& v1, const Vector& v2);
Vector operator-(const Vector& v1, const Vector& v2);

const Vector VECTOR_POISON(COORD_POISON, COORD_POISON);

class RectangleArea{
public:
    RectangleArea(Vector pos, Vector size);
    RectangleArea(Vector size);
    ~RectangleArea();

public:
    Vector pos;
    Vector size;
};

/**
 * @brief to contain double from 0 to 1
 * 
 */
class ProportionRatio{
public:
    ProportionRatio(double val);

    void operator=(double val);
    operator double() const;
private:
    double val_;
};

/**
 * @brief contains data for displaying text
 * 
 */
class Text{
public:
    Text();
    Text(const std::string& text);
public:
    coord       font_size;
    std::string str;
    Color       col;
};

#endif // AUXIL_H
