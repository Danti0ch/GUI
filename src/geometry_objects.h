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

private:   
    double x_, y_;

public: 
    Vector();
    Vector(double v1, double v2, VT_DATA mod);

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

    ~Vector(){}
};

std::ostream& operator<<(std::ostream &os, const Vector& v);
//----------------------------------------------------------------------------------------//

class Vector3D{

private:   

    double x_, y_, z_;
public:

    Vector3D();
    Vector3D(double x, double y, double z);

    double x()   const { return x_; }
    double y()   const { return y_; }
    double z()   const { return z_; }

    void x(double x) { x_ = x; }
    void y(double y) { y_ = y; }
    void z(double z) { z_ = z; }

    double len() const;
    
    void ChangeLen(double len_val);

    void operator +=(const Vector3D &v2);
    void operator -=(const Vector3D &v2);
    void operator *=(double ratio);
    void operator /=(double ratio);

    Vector3D operator +(const Vector3D &v2) const;
    Vector3D operator -(const Vector3D &v2) const;
    Vector3D operator *(double ratio) const;
    Vector3D operator /(double ratio) const;
    Vector3D operator -() const;

    ~Vector3D(){}
};

double CountCosAngle(const Vector3D& v1, const Vector3D& v2);
double CountSinAngle(const Vector3D& v1, const Vector3D& v2);
double CountScalarMul(const Vector3D& v1, const Vector3D& v2);

std::ostream& operator<<(std::ostream &os, const Vector3D& v);
//----------------------------------------------------------------------------------------//

class Sphere{

private:
    Vector3D center_;
    double r_;

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
};
//----------------------------------------------------------------------------------------//

class Plane{

private:
    double a_, b_, c_, d_;
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
};

double GetIntersectionRatio(const Vector3D& base, const Vector3D& dir, const Sphere& sp);
double GetIntersectionRatio(const Vector3D& base, const Vector3D& dir, const Plane& plane);

} // namespace geom

#endif // GEOM_OBJS_H
