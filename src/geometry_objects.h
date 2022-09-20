#ifndef GEOM_OBJS_H
#define GEOM_OBJS_H

class Point;
class Ray;
class Plane;
class Line;
class Vector3D;

const enum INTERSECTION_MOD{

    NO_INTER,
    POINTS,
    RAY
};

class Ray{

private:
    Vector  pt_;
    Vector3D vt_;

public:

    // TODO: написать перегрузки
    Ray(const Point& pt, const Vector& vt): pt_(pt), vt_(vt){}

    INTERSECTION_MOD GetRaysIntersection(const Ray& ray2, std::Vector& storage);
    INTERSECTION_MOD GetRayPlaneInterSection(const Plane& plane, std::Vector& storage);
    INTERSECTION_MOD GetRayPolylineInterSection(const Plane* planes, std::Vector& storage);
};

class Plane{

private:
    double a_, b_, c_, d_;
public:

    Plane(double a, double b, double c, double d): a_(a), b_(b), c_(c), d_(d){}
};

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

#endif // GEOM_OBJS_H

/*
class Line{

private:
    Point    pt_;
    Vector3D vt_;

public:

    // TODO: написать перегрузки
    Line(const Point& pt, const Vector& vt): pt_(pt), vt_(vt){}
};
*/
