#ifndef RAYTRAY
#define RAYTRAY

#include "graphic_lib_wrapper.h"
#include "geometry_objects.h"

const double   AMBIENT_VAL        = 0.6;
const uint     SPECULAR_POW_RATIO = 3;

const double   DIFFUSE_RATIO   = 1.8;
const double   AMBIENT_RATIO   = 1.2;
const double   SPECULAR_RATIO  = 0.6;

class Light{

    gglib::Color col_;

public:
   geom::Vector3D pos;
   //geom::Vector3D dir;

    Light(const geom::Vector3D& pos, gglib::Color col = gglib::Color(255, 244, 79)):
        pos(pos), col_(col) {}

    Light(double px, double py, double pz, gglib::Color col = gglib::Color(255, 244, 79)):
        pos(px, py, pz), col_(col) {}

    gglib::Color col() const { return col_; }    
};
//----------------------------------------------------------------------------------------//

class Camera{

public:
   geom::Vector3D pos;
   geom::Vector3D dir;

    Camera(const geom::Vector3D& pos, const geom::Vector3D& dir):
        pos(pos), dir(dir) {}

    Camera(double px, double py, double pz,
          double dx, double dy, double dz):
        pos(px, py, pz), dir(dx, dy, dz) {}

};
//----------------------------------------------------------------------------------------//

class Sphere : public geom::Sphere{

private:
    gglib::Color col_;

public:

    Sphere(double x0, double y0, double z0, double r, gglib::Color col = gglib::Color(255, 0, 0));
    Sphere(const geom::Vector3D& v, double r, gglib::Color col = gglib::Color(255, 0, 0));
    
    gglib::Color GetColor(const geom::Vector3D& pt, const Camera& cam, const std::vector<Light>& lights) const;
};
//----------------------------------------------------------------------------------------//

class SceneRaytracer : public gglib::GraphicSpace{

private:
    void KeyPressHandler(gglib::Key key);
    void UpdateAfterEvents();

public:

    Light  light_source;
    Camera cam;

    Sphere spheres[3];

    SceneRaytracer();
};
//----------------------------------------------------------------------------------------//

#endif // RAYTRAY
