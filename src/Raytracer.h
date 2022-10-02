#ifndef RAYTRAY
#define RAYTRAY

#include "graphic_lib_wrapper.h"
#include "geometry_objects.h"

#ifndef CONTOUR_ENABLED
    #define CONTOUR_ENABLED 0
#endif

class Sphere;

struct Material{
    gglib::Color col;
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
    gglib::Color(248, 248, 255), 1, 400, {0, 0.7, 0, 1.4, 0}
};

const Material GlassMaterial{
    gglib::Color(168, 204, 215), 1.5, 120, {0.3, 0.12, 0.48, 0.6, 0.6}
};
const Material SteelMaterial{
    gglib::Color(142, 154, 175), 1, 50, {0.3, 0, 0, 0.9, 0.6}
};
const Material TreeMaterial{
    gglib::Color(143, 88, 60), 1, 500, {0.9, 0.06, 0, 0.3, 0.6}
};
const Material LightMaterial{
    gglib::Color(255, 255, 255, 255), 1, 0, {0, 0, 0, 0, 0}
};

class Camera{

private:
    geom::Vector3D pos_;
    geom::Vector3D dir_;

public:

    Camera(const geom::Vector3D& pos, const geom::Vector3D& dir):
        pos_(pos), dir_(dir) {}

    Camera(double px, double py, double pz,
          double dx, double dy, double dz):
        pos_(px, py, pz), dir_(dx, dy, dz) {}

    geom::Vector3D pos() const { return pos_; }
    geom::Vector3D dir() const { return dir_; }

    void pos(const geom::Vector3D& v) { pos_ = v; }
    void dir(const geom::Vector3D& v) { dir_ = v; }
};
//----------------------------------------------------------------------------------------//

class Sphere : public geom::Sphere{

    Material mat_;
public:

    Sphere(double x0, double y0, double z0, double r, const Material& mat):
        geom::Sphere(x0, y0, z0, r), mat_(mat) {}

    Sphere(const geom::Vector3D& v, double r, const Material& mat):
        geom::Sphere(v, r), mat_(mat) {}

    double GetIntersectionRatio(const geom::Vector3D& base, const geom::Vector3D& dir) const;
    
    Material mat() const { return mat_; }
};
//----------------------------------------------------------------------------------------//

class SphereLight{

private:
    Sphere          shape_;
    gglib::Color    col_;
    geom::Vector3D  pos_;

public:

    SphereLight(const geom::Vector3D& pos, gglib::Color col = gglib::Color(255, 244, 79)):
        pos_(pos), col_(col), shape_(pos, 0.3, LightMaterial) {}

    SphereLight(double px, double py, double pz, gglib::Color col = gglib::Color(255, 244, 79)):
        pos_(px, py, pz), col_(col), shape_(px, py, pz, 0.3, LightMaterial) {}

    Sphere         shape() const { return shape_; }
    gglib::Color   col()   const { return col_; }
    geom::Vector3D pos()   const { return pos_; }
};
//----------------------------------------------------------------------------------------//

class Plane : public geom::Plane{
private:
    Material mat_;
public:

    Plane(double a, double b, double c, double d, const Material& mat):
        geom::Plane(a, b, c, d), mat_(mat){}
    
    Plane(const geom::Vector3D& pt, const geom::Vector3D& v1, const geom::Vector3D& v2, const Material& mat):
        geom::Plane(pt, v1, v2), mat_(mat){}

    Plane(const geom::Vector3D& pt, const geom::Vector3D& norm, const Material& mat):
        geom::Plane(pt, norm), mat_(mat){}
    
    double GetIntersectionRatio(const geom::Vector3D& base, const geom::Vector3D& dir) const;
    
    Material mat() const { return mat_; }
};
//----------------------------------------------------------------------------------------//

enum class SHAPE_ID{
    WRONG,
    SPHERE,
    PLANE
};

class SceneRaytracer : public gglib::GraphicSpace{

private:
    void KeyPressHandler(gglib::Key key);
    void UpdateAfterEvents();

public:

    gglib::Color background_col;
    SphereLight  light_source[1];
    Camera cam;

    // TODO: to vector<>
    Sphere spheres[4];
    Plane  planes[1];

    SceneRaytracer();
};
//----------------------------------------------------------------------------------------//

geom::Vector3D GetReflectedVector(const geom::Vector3D& pt, const geom::Vector3D& norm);
geom::Vector3D GetReflectedVector(const geom::Vector3D& pt, const geom::Sphere& obj);
geom::Vector3D GetReflectedVector(const geom::Vector3D& pt, const geom::Plane& obj);

#endif // RAYTRAY
