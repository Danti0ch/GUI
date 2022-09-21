#include "geometry_objects.h"
#include <math.h>

static const double EPS = 1e-8;

double get_quad_eq_root(double a, double b, double c);

#include <iostream>

double GetIntersectionRatio(const Vector3D& base, const Vector3D& dir, const Sphere& sp){

    double t1 = base.x() - sp.x0();
    double t2 = base.y() - sp.y0();
    double t3 = base.z() - sp.z0();
    
    double k1 = dir.x() * dir.x() + dir.y() * dir.y() + dir.z() * dir.z();
    double k2 = 2 * (dir.x() * t1 + dir.y() * t2 + dir.z() * t3);
    double k3 = t1 * t1 + t2 * t2 + t3 * t3 - sp.r() * sp.r();

    double root = get_quad_eq_root(k1, k2, k3);

    return root;
}
//----------------------------------------------------------------------------------------//

double get_quad_eq_root(double a, double b, double c){

    if(fabs(a) < EPS){
        if(fabs(b) < EPS){
            return NAN;
        }
        return -c / b;
    }
    
    double d = b * b - 4 * a * c;

    if(d < -EPS){
        return NAN;
    }

    else if(d < EPS) d = 0;

    if(a >= EPS){

        double v1 = (-b - sqrt(d)) / (2 * a);
        if(v1 < EPS){
            return (-b + sqrt(d)) / (2 * a);
        }
        return v1;
    }

    return (-b + sqrt(d)) / (2 * a);
}
//----------------------------------------------------------------------------------------//
