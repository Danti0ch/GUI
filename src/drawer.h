#ifndef DRAWER_H
#define DRAWER_H

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Vertex.hpp>

typedef unsigned int uint;

// TODO: чекнуть констатные методы и ошибку 
// Declaring a member function with the const keyword specifies that the function is a "read-only" function that doesn't modify the object for which it's called. A constant member function can't modify any non-static data members or call any member functions that aren't constant. To declare a constant member function, place the const keyword after the closing parenthesis of the argument list. The const keyword is required in both the declaration and the definition.
class Point{

public:

private:
    double x_, y_;
public:
    Point(double x, double y);

    double x() const { return x_; }
    double y() const { return y_; }

    ~Point(){}
};
//----------------------------------------------------------------------------------------//

class CoordinateSus{

private:
    
    double x_lower_lim_, x_upper_lim_;
    double y_lower_lim_, y_upper_lim_;

    int x_lower_pixel_, x_upper_pixel_;
    int y_lower_pixel_, y_upper_pixel_;

    int n_x_upper_axis_pixels_, n_x_lower_axis_pixels_;
    int n_y_upper_axis_pixels_, n_y_lower_axis_pixels_;
    
    double scale_x_, scale_y_;
    double step_val_;
public:
    
    CoordinateSus(uint x_lower_pixel, uint x_upper_pixel, uint y_lower_pixel, uint y_upper_pixel,
                  double x_lower_lim, double x_upper_lim, double y_lower_lim, double y_upper_lim);

    double x_lower_lim(){ return x_lower_lim_; }
    double x_upper_lim(){ return x_upper_lim_; }
    double y_lower_lim(){ return y_lower_lim_; }
    double y_upper_lim(){ return y_upper_lim_; }
    
    double x_lower_pixel(){ return x_lower_pixel_; }
    double x_upper_pixel(){ return x_upper_pixel_; }
    double y_lower_pixel(){ return y_lower_pixel_; }
    double y_upper_pixel(){ return y_upper_pixel_; }
    
    double scale_x(){ return scale_x_; }
    double scale_y(){ return scale_y_; }
    double step_val(){ return step_val_; }
    
    int CountPixelPosX(double x_ct);
    int CountPixelPosY(double y_ct);

    double CountAxisPosX(int x_pixel);
    double CountAxisPosY(int y_pixel);
    
    int CountPixelPosX(Point* pt);
    int CountPixelPosY(Point* pt);

    void Draw(sf::RenderWindow* window);
    ~CoordinateSus(){}
};
//----------------------------------------------------------------------------------------//

// TODO: mb other way??
enum class VT_DATA{
    POLAR,
    COORD
};

// TODO: конструктор по умолчанию
class Vector{

private:   

    double x_, y_;
    double angle_;
    double len_;
public:

    Vector(double v1, double v2, VT_DATA data_type);
    // TODO: to const
    Vector(Point* ct);
    //Vector(double x_offset, double y_offset, Vector* vt_from);

//    Point GetFinalPoint();

    void Draw(sf::RenderWindow* window, CoordinateSus* ct_sus);
    void Draw(sf::RenderWindow* window, CoordinateSus* ct_sus, Point* ct_init);
    void Draw(sf::RenderWindow* window, CoordinateSus* ct_sus, double x_init, double y_init);
    void Draw(sf::RenderWindow* window, CoordinateSus* ct_sus, Vector* vt_init);

    double x() const { return x_; }
    double y() const { return y_; }

    double len()   const { return len_; }
    double angle() const { return angle_; }
    //double tg(){ return angle_; }
    //double len()  { return len_; }

    // TODO: уточнить является ли это корректным
    Vector NormalVector();
    void   Normalize();

    void ChangeLen(double len_val);

    Vector operator +(const Vector &v2);
    Vector operator -(const Vector &v2);
    Vector operator *(double ratio);
    Vector operator /(double ratio);

    Vector operator -();

    ~Vector(){}
};
//----------------------------------------------------------------------------------------//

#endif // DRAWER_H