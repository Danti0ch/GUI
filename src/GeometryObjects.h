#ifndef GEOM_OBJS_H
#define GEOM_OBJS_H

#include <iostream>

namespace geom{

const double EPS = 1e-8;

enum VT_DATA{
    POLAR,
    COORD
};

class Vector{

public: 
    Vector();
    Vector(double v1, double v2, VT_DATA mod);

    ~Vector(){}

    double x() const { return x_; }
    double y() const { return y_; }
    
    void x(double x) { x_ = x; }
    void y(double y) { y_ = y; }
    
    double len() const;

    Vector NormalVector(double len = 1) const;
    void   Normalize();

    void ChangeLen(double len_val);

    Vector operator  +(const Vector &v2) const;
    Vector operator  -(const Vector &v2) const;
    Vector operator  *(double ratio)     const;
    Vector operator  /(double ratio)     const;

    void   operator +=(const Vector& v);
    void   operator -=(const Vector& v);
    void   operator *=(double ratio);
    void   operator /=(double ratio);

    Vector operator  -() const;

private:   
    double x_, y_;
};

std::ostream& operator<<(std::ostream &os, const Vector& v);
//----------------------------------------------------------------------------------------//

class Vector3D{
public:

    Vector3D();
    Vector3D(double x, double y, double z);

    ~Vector3D(){}

    double x()   const { return x_; }
    double y()   const { return y_; }
    double z()   const { return z_; }

    void x(double x) { x_ = x; }
    void y(double y) { y_ = y; }
    void z(double z) { z_ = z; }

    double len() const;
    
    void ChangeLen(double len_val);
    void Normalize();

    void operator +=(const Vector3D &v2);
    void operator -=(const Vector3D &v2);
    void operator *=(double ratio);
    void operator /=(double ratio);

    Vector3D operator +(const Vector3D &v2) const;
    Vector3D operator -(const Vector3D &v2) const;
    Vector3D operator *(double ratio) const;
    Vector3D operator /(double ratio) const;
    Vector3D operator -() const;

private:
    double x_, y_, z_;
};

double CountCosAngle(const Vector3D& v1, const Vector3D& v2);
double CountSinAngle(const Vector3D& v1, const Vector3D& v2);
double CountScalarMul(const Vector3D& v1, const Vector3D& v2);

std::ostream& operator<<(std::ostream &os, const Vector3D& v);
//----------------------------------------------------------------------------------------//

class Sphere{
public:
    Sphere(double x0, double y0, double z0, double r):
        center_(x0, y0, z0), r_(r){}
    Sphere(const Vector3D& v, double r):
        center_(v), r_(r){}
    
    double x0() const { return center_.x(); }
    double y0() const { return center_.y(); }
    double z0() const { return center_.z(); }

    Vector3D center() const { return center_; }
    double  r() const { return r_; }

    Vector3D GetNormal(const Vector3D& pt) const;
        
    bool CheckPointIn(double x, double y, double z) const;
    bool CheckPointIn(const Vector3D& vt) const;
    
    double GetIntersectionRatio(const Vector3D& base, const Vector3D& dir) const;
private:
    Vector3D center_;
    double r_;
};
//----------------------------------------------------------------------------------------//

class Plane{
public:
    Plane(double a, double b, double c, double d):
        a_(a), b_(b), c_(c), d_(d){}
    Plane(const Vector3D& pt, const Vector3D& v1, const Vector3D& v2);
    Plane(const Vector3D& pt, const Vector3D& norm);

    Vector3D GetNormal(const Vector3D& vt) const;

    double a() const { return a_; }
    double b() const { return b_; }
    double c() const { return c_; }
    double d() const { return d_; }

    bool CheckPointIn(double x, double y, double z) const;
    bool CheckPointIn(const Vector3D& vt) const;
    double GetIntersectionRatio(const Vector3D& base, const Vector3D& dir) const;

private:
    double a_, b_, c_, d_;
};

#include <stdlib.h>

class CoordinateSus{
public:
    
    CoordinateSus(uint x_lower_pixel, uint x_upper_pixel, uint y_lower_pixel, uint y_upper_pixel,
                  double x_lower_lim, double x_upper_lim, double y_lower_lim, double y_upper_lim);

    ~CoordinateSus(){}

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
private:
    
    double x_lower_lim_, x_upper_lim_;
    double y_lower_lim_, y_upper_lim_;

    int x_lower_pixel_, x_upper_pixel_;
    int y_lower_pixel_, y_upper_pixel_;

    int n_x_upper_axis_pixels_, n_x_lower_axis_pixels_;
    int n_y_upper_axis_pixels_, n_y_lower_axis_pixels_;
    
    double scale_x_, scale_y_;
    double step_val_;
};

int CheckCoordInCTS(const CoordinateSus& cts, uint x, uint y);
//----------------------------------------------------------------------------------------//

} // namespace geom


#endif // GEOM_OBJS_H
