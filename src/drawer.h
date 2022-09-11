#ifndef DRAWER_H
#define DRAWER_H

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Vertex.hpp>

typedef unsigned int uint;

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

    double x_lower_lim() const { return x_lower_lim_; }
    double x_upper_lim() const { return x_upper_lim_; }
    double y_lower_lim() const { return y_lower_lim_; }
    double y_upper_lim() const { return y_upper_lim_; }
    
    int x_lower_pixel() const { return x_lower_pixel_; }
    int x_upper_pixel() const { return x_upper_pixel_; }
    int y_lower_pixel() const { return y_lower_pixel_; }
    int y_upper_pixel() const { return y_upper_pixel_; }
    
    double scale_x()  const { return scale_x_; }
    double scale_y()  const { return scale_y_; }
    double step_val() const { return step_val_; }
    
    int CountPixelPosX(double x_ct) const;
    int CountPixelPosY(double y_ct) const;

    double CountAxisPosX(int x_pixel) const;
    double CountAxisPosY(int y_pixel) const;

    void Draw(sf::RenderWindow* window) const;
    ~CoordinateSus(){}
};
//----------------------------------------------------------------------------------------//

// TODO: think about other way of distinguish arguments of constructor
enum class VT_DATA{
    POLAR,
    COORD
};

class Vector{

private:   

    double x_, y_;
    double angle_;
    double len_;
public:

    Vector();
    Vector(double v1, double v2, VT_DATA data_type);

    void Draw(sf::RenderWindow* window, const CoordinateSus& ct_sus) const;
    void Draw(sf::RenderWindow* window, const CoordinateSus& ct_sus, double x_init, double y_init) const;
    void Draw(sf::RenderWindow* window, const CoordinateSus& ct_sus, const Vector& vt_init) const;

    double x() const { return x_; }
    double y() const { return y_; }

    double len()   const { return len_; }
    double angle() const { return angle_; }

    Vector NormalVector(double len = 1) const;
    void   Normalize();

    void ChangeLen(double len_val);

    Vector operator +(const Vector &v2) const;
    Vector operator -(const Vector &v2) const;
    Vector operator *(double ratio) const;
    Vector operator /(double ratio) const;

    Vector operator -() const;

    ~Vector(){}
};
//----------------------------------------------------------------------------------------//

// TODO: изменить каталогизацию
class Vector3D{

private:   

    double x_, y_, z_;
    double len_;
public:

    Vector3D();
    Vector3D(double x, double y, double z);

    double x()   const { return x_; }
    double y()   const { return y_; }
    double z()   const { return z_; }

    double len() const { return len_; }
    
    void ChangeLen(double len_val);

    Vector3D operator +(const Vector3D &v2) const;
    Vector3D operator -(const Vector3D &v2) const;

    ~Vector3D(){}
};

double CountCosAngle(const Vector3D& v1, const Vector3D& v2);
void DrawSphere();

#endif // DRAWER_H