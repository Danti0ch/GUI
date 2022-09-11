#ifndef DRAWER_H
#define DRAWER_H

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Vertex.hpp>

typedef unsigned int uint;

class Point{

public:

private:
    double x_, y_;
public:
    Point(double x, double y);

    double x(){ return x_; }
    double y(){ return y_; }

    ~Point(){}
};
//----------------------------------------------------------------------------------------//

class CoordinateSus{

private:
    
    double x_lower_lim_, x_upper_lim_;
    double y_lower_lim_, y_upper_lim_;

    int x_lower_pixel_, x_upper_pixel_;
    int y_lower_pixel_, y_upper_pixel_;

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
    int CountPixelPosX(Point* pt);
    int CountPixelPosY(Point* pt);

    ~CoordinateSus(){}
};
//----------------------------------------------------------------------------------------//

class Vector{

private:    

    double x_, y_;
public:

    Vector(double x, double y);

    // TODO: to const
    Vector(Point* ct);
    //Vector(double x_offset, double y_offset, Vector* vt_from);

//    Point GetFinalPoint();

    void Draw(sf::RenderWindow* window, CoordinateSus* ct_sus);
    void Draw(sf::RenderWindow* window, CoordinateSus* ct_sus, Point* ct_init);
    void Draw(sf::RenderWindow* window, CoordinateSus* ct_sus, double x_init, double y_init);
    void Draw(sf::RenderWindow* window, CoordinateSus* ct_sus, Vector* vt_init);

    double x(){ return x_; }
    double y(){ return y_; }

    ~Vector(){}
};
//----------------------------------------------------------------------------------------//

void DrawGraphic(sf::RenderWindow* window, CoordinateSus* ct_sus);

#endif // DRAWER_H