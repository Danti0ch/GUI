#include "drawer.h"
#include <assert.h>
#include <math.h>

static const double EPS = 1e-8;

Vector3D::Vector3D(double x, double y, double z):
    x_(x),
    y_(y),
    z_(z)
{
    len_ = sqrt(x_ * x_ + y_ * y_ + z_ * z_);

//    assert(len_ > EPS);
}
//----------------------------------------------------------------------------------------//

Vector3D::Vector3D():
    x_(1),
    y_(1),
    z_(1)
{
    len_ = sqrt(x_ * x_ + y_ * y_ + z_ * z_);
}
//----------------------------------------------------------------------------------------//

Vector3D Vector3D::operator +(const Vector3D &v2) const {
    return Vector3D(x_ + v2.x(), y_ + v2.y(), z_ + v2.z());
}
//----------------------------------------------------------------------------------------//

Vector3D Vector3D::operator -(const Vector3D &v2) const {
    return Vector3D(x_- v2.x(), y_ - v2.y(), z_ - v2.z());
}
//----------------------------------------------------------------------------------------//

double CountCosAngle(const Vector3D& v1, const Vector3D& v2) const {

    double scalar_mul = v1.x() * v2.x() + v1.y() * v2.y() + v1.z() * v2.z();

    return scalar_mul / (v1.len() * v2.len());
}
//----------------------------------------------------------------------------------------//

void Vector3D::ChangeLen(double len_val){

    assert(len_val > EPS);

    x_  *= len_val / len_;
    y_  *= len_val / len_;
    z_  *= len_val / len_;
    len_ = len_val;

    return;
}
//----------------------------------------------------------------------------------------//
