#ifndef RAYTRAY
#define RAYTRAY

#include "scene_objects.h"

#ifndef CONTOUR_ENABLED
    #define CONTOUR_ENABLED 0
#endif

const uint N_SHAPES = 5;

class SceneRaytracer{
public:

    SceneRaytracer();
    ~SceneRaytracer();
    
    gglib::Color background_col;
    Camera cam;

    dts::vector<SphereLight> light_sources;
    dts::vector<Shape*> shapes;

private:
    void KeyPressHandler(gglib::Key key);
    void UpdateAfterEvents();
};
//----------------------------------------------------------------------------------------//

#endif // RAYTRAY
