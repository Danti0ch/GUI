#ifndef GEOM_OBJS_H
#define GEOM_OBJS_H

namespace geom{
enum class VT_DATA{
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

    ~Vector3D(){}
};

double CountCosAngle(const Vector3D& v1, const Vector3D& v2);
//----------------------------------------------------------------------------------------//

class Sphere{

private:
    double x0_, y0_, z0_;
    double r_;
public:
    Sphere(double x0, double y0, double z0, double r):
        x0_(x0), y0_(y0), z0_(z0), r_(r){}
    Sphere(const Vector3D& v, double r):
        x0_(v.x()), y0_(v.y()), z0_(v.z()), r_(r){}
    
    double x0() const { return x0_; }
    double y0() const { return y0_; }
    double z0() const { return z0_; }
    double  r() const { return r_; }
};

double GetIntersectionRatio(const Vector3D& base, const Vector3D& dir, const Sphere& sp);
//----------------------------------------------------------------------------------------//

} // namespace geom

#endif // GEOM_OBJS_H
