#include "geometry_objects.h"
#include <math.h>
#include <assert.h>
#include <limits.h>

using namespace geom;

// TODO: convert to determinant sol??
Plane::Plane(const Vector3D& pt, const Vector3D& v1, const Vector3D& v2){

    a_ = v1.y() * v2.z() - v1.z() * v2.y();
    b_ = v1.z() * v2.x() - v1.x() * v2.z();
    c_ = v1.x() * v2.y() - v1.y() * v2.x();

    d_ = - pt.x() * v1.y() * v2.z() - pt.z() * v1.x() * v2.y() +
         - pt.y() * v1.z() * v2.x() + pt.z() * v1.y() * v2.x() +
           pt.x() * v1.z() * v2.y() + pt.y() * v1.x() * v2.z();
}
//----------------------------------------------------------------------------------------//

Plane::Plane(const Vector3D& pt, const Vector3D& norm){
    
    a_ = norm.x();
    b_ = norm.y();
    c_ = norm.z();

    d_ = -norm.x() * pt.x() - norm.y() * pt.y() - norm.z() * pt.z();
}
//----------------------------------------------------------------------------------------//

Vector3D Plane::GetNormal(const Vector3D& vt) const{

    Vector3D norm = Vector3D(a_, b_, c_);

    if(CountCosAngle(vt, norm) < EPS){
        return -norm;
    }
    return norm;
}
//----------------------------------------------------------------------------------------//

bool Plane::CheckPointIn(double x, double y, double z)  const{

    return fabs(a_ * x + b_ * y + c_ * z) < EPS;
}
//----------------------------------------------------------------------------------------//

bool Plane::CheckPointIn(const Vector3D& vt) const{

    return CheckPointIn(vt.x(), vt.y(), vt.z());
}
//----------------------------------------------------------------------------------------//

double geom::GetIntersectionRatio(const Vector3D& base, const Vector3D& dir, const Plane& plane){

    double coef = plane.a() * dir.x() + plane.b() * dir.y() + plane.c() * dir.z();

    if(fabs(coef) < EPS) return NAN;

    double ratio =  (-plane.d() - plane.a() * base.x() - plane.b() * base.y() - plane.c() * base.z())
                                / coef;

    //if(ratio > UPPER_LIM) return NAN;

    return ratio;
}
//----------------------------------------------------------------------------------------//
