#ifndef SCENE_OBJECTS_H
#define SCENE_OBJECTS_H

#include "geometry_objects.h"
#include "Color.h"
#include <math.h>

struct Material{
    Color col;
    double       refract_ratio;
    uint         shininess_ratio;
    double       koef[5];
};
//----------------------------------------------------------------------------------------//

enum KOEF_VAL{

    DIFFUSE,
    REFLECT,
    REFRACT,
    SPECULAR,
    AMBIENT
};

const Material MirrorMaterial{
    Color(248, 248, 255), 1, 1000, {0, 0.7, 0, 1.2, 0}
};
const Material GlassMaterial{
    Color(112, 194, 180), 1.5, 100, {0, 0, 0.6, 0.3, 0.15}
};
const Material SteelMaterial{
    Color(142, 154, 175), 1, 1200, {1, 0, 0, 1.2, 0.6}
};
const Material TreeMaterial{
    Color(143, 88, 60), 1, 1000, {0.9, 0.06, 0, 0.3, 0.6}
};
const Material LightMaterial{
    Color(255, 200, 200, 255), 1, 0, {0, 0, 0, 0, 0}
};
const Material GrassMaterial{
    Color(112, 194, 180) , 1, 0, {0.9, 0, 0, 0, 0.5}
};

class Camera{
public:

    Camera(const geom::Vector3D& pos, const geom::Vector3D& dir, double view_angle = M_PI / 2):
        pos_(pos), dir_(dir), view_angle_(view_angle) {}

    Camera(double px, double py, double pz,
          double dx, double dy, double dz, double view_angle = M_PI / 2):
        pos_(px, py, pz), dir_(dx, dy, dz), view_angle_(view_angle) {}

    geom::Vector3D& pos() { return pos_; }
    geom::Vector3D& dir() { return dir_; }
    double view_angle() const { return view_angle_; }

    void pos(const geom::Vector3D& v) { pos_ = v; }
    void dir(const geom::Vector3D& v) { dir_ = v; }
private:
    geom::Vector3D pos_;
    geom::Vector3D dir_;
    double view_angle_;
};
//----------------------------------------------------------------------------------------//

class Shape{
public:
    Shape(const Material& mat):
        mat_(mat) {}
    
    virtual double GetIntersectionRatio(const geom::Vector3D& base, const geom::Vector3D& dir) const = 0;
    virtual geom::Vector3D GetNormal(const geom::Vector3D& pt) const = 0;

    Material mat() const { return mat_; }   
private:
    Material mat_; 
};
//----------------------------------------------------------------------------------------//

class Sphere : public geom::Sphere, public Shape{
public:

    Sphere(double x0, double y0, double z0, double r, const Material& mat):
        geom::Sphere(x0, y0, z0, r), Shape(mat) {
        }

    Sphere(const geom::Vector3D& v, double r, const Material& mat):
        geom::Sphere(v, r), Shape(mat) {}

    double GetIntersectionRatio(const geom::Vector3D& base, const geom::Vector3D& dir) const{
        return geom::Sphere::GetIntersectionRatio(base, dir);
    }

    geom::Vector3D GetNormal(const geom::Vector3D& pt) const{
        return geom::Sphere::GetNormal(pt);
    }
};
//----------------------------------------------------------------------------------------//

class SphereLight{
public:

    SphereLight():
        pos_(geom::Vector3D(0, 0, 0)), col_(Color(0, 0, 0, 0)), shape_(pos_, 0.3, LightMaterial) {}

    SphereLight(const geom::Vector3D& pos, Color col = Color(255, 244, 79)):
        pos_(pos), col_(col), shape_(pos, 0.3, LightMaterial) {}

    SphereLight(double px, double py, double pz, Color col = Color(255, 244, 79)):
        pos_(px, py, pz), col_(col), shape_(px, py, pz, 0.3, LightMaterial) {}

    Sphere         shape() const { return shape_; }
    Color   col()   const { return col_; }
    geom::Vector3D pos()   const { return pos_; }
private:
    Sphere          shape_;
    Color    col_;
    geom::Vector3D  pos_;
};
//----------------------------------------------------------------------------------------//

class Plane : public geom::Plane, public Shape{
public:

    Plane(double a, double b, double c, double d, const Material& mat):
        geom::Plane(a, b, c, d), Shape(mat){}
    
    Plane(const geom::Vector3D& pt, const geom::Vector3D& v1, const geom::Vector3D& v2, const Material& mat):
        geom::Plane(pt, v1, v2), Shape(mat){}

    Plane(const geom::Vector3D& pt, const geom::Vector3D& norm, const Material& mat):
        geom::Plane(pt, norm), Shape(mat){}
    
    double GetIntersectionRatio(const geom::Vector3D& base, const geom::Vector3D& dir) const{
        return geom::Plane::GetIntersectionRatio(base, dir);
    }

    geom::Vector3D GetNormal(const geom::Vector3D& pt) const{
        return geom::Plane::GetNormal(pt);
    }
};
//----------------------------------------------------------------------------------------//

#endif // SCENE_OBJECTS_H