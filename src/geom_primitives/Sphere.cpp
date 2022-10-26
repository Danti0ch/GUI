#include "GeometryObjects.h"
#include <math.h>
#include <assert.h>
using namespace geom;


/// @brief выдаёт минимальный положительный корень квадратного уравнения или NAN, если такого нет
double get_quad_eq_root(double a, double b, double c);

double Sphere::GetIntersectionRatio(const Vector3D& base, const Vector3D& dir) const {

    double t1 = base.x() - center_.x();
    double t2 = base.y() - center_.y();
    double t3 = base.z() - center_.z();
    
    double k1 = dir.x() * dir.x() + dir.y() * dir.y() + dir.z() * dir.z();
    double k2 = 2 * (dir.x() * t1 + dir.y() * t2 + dir.z() * t3);
    double k3 = t1 * t1 + t2 * t2 + t3 * t3 - r_ * r_;

    double root = get_quad_eq_root(k1, k2, k3);

    if(!std::isnan(root)){
        if(fabs(k1 * root * root + k2 * root + k3) >= geom::EPS){
            return NAN;
        }
    }
    
    return root;
}
//----------------------------------------------------------------------------------------//

#define min(a, b) ((a) < (b) ? (a) : (b))

double get_quad_eq_root(double a, double b, double c){

    if(fabs(a) < EPS){
        if(fabs(b) < EPS) return NAN;
        return -c / b;
    }
    
    double d = b * b - 4 * a * c;
    if(d < -EPS) return NAN;

    else if(d < EPS) d = 0;

    double tmp  = sqrt(d)/(2*a);
    double tmp2 = -b / (2*a);
    
    double v1 = tmp + tmp2;
    double v2 = -tmp + tmp2;

    if(v1 < EPS){
        if(v2 < EPS) return NAN;
        return v2;
    }
    if(v2 < EPS){
        if(v1 < EPS) return NAN;
        return v1;
    }
    else{
        return min(v1, v2);
    }
}
//----------------------------------------------------------------------------------------//

bool Sphere::CheckPointIn(double x, double y, double z) const {

    double summ = (x - center_.x()) * (x - center_.x()) + (y - center_.y()) * (y - center_.y()) + (z - center_.z()) * (z - center_.z());
    if(fabs(r_ * r_ - summ) < EPS) return true;
    return false;
}

bool Sphere::CheckPointIn(const Vector3D& vt) const {

    return CheckPointIn(vt.x(), vt.y(), vt.z());
}
//----------------------------------------------------------------------------------------//

Vector3D Sphere::GetNormal(const Vector3D& pt) const{

    if(!CheckPointIn(pt)){
        return geom::Vector3D(NAN, NAN, NAN);
    }

    return pt - center_;
}
//----------------------------------------------------------------------------------------//
