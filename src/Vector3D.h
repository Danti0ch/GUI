#ifndef VECTOR3D_H
#define VECTOR3D_H

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

    Vector3D operator *(double ratio) const;
    Vector3D operator /(double ratio) const;

    ~Vector3D(){}
};

double CountCosAngle(const Vector3D& v1, const Vector3D& v2);

#endif // VECTOR3D_H