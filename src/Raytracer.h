#ifndef RAYTRACER_H
#define RAYTRACER_H

#include "Widget.h"
#include "SceneObjects.h"

#ifndef CONTOUR_ENABLED
    #define CONTOUR_ENABLED 0
#endif

class Raytracer : public Widget{
public:

    Raytracer(uint x, uint y, uint width, uint height);
    ~Raytracer(){}
    
    void draw() override;

    std::vector<SphereLight>& light_sources()   { return light_sources_; }  
    std::vector<Shape*>&      shapes()          { return shapes_; }
    Color&                    background_col()  { return background_col_; }
    Camera&                   cam()             { return cam_; }

private:

    // TODO: to list
    std::vector<SphereLight> light_sources_;
    std::vector<Shape*> shapes_;

    Color background_col_;
    Camera cam_;
};

#endif // RAYTRACER_H
