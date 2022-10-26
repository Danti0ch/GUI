#ifndef DRAW_AREA_H
#define DRAW_AREA_H

#include "SceneObjects.h"
#include "gui/Widget.h"

#ifndef CONTOUR_ENABLED
    #define CONTOUR_ENABLED 0
#endif

class Raytracer : public Widget{
public:

    Raytracer(ContainerWidget* parent_widget, uint x, uint y, uint width, uint height);
    ~Raytracer(){}
    
    void draw(GraphicSpace* space) override;

    std::vector<SphereLight>& light_sources()   { return light_sources_; }  
    std::vector<Shape*>&       shapes()          { return shapes_; }
    Color&                    background_col()  { return background_col_; }
    Camera&                   cam()             { return cam_; }

private:

    // TODO: to list
    std::vector<SphereLight> light_sources_;
    std::vector<Shape*> shapes_;

    Color background_col_;
    Camera cam_;
};

#endif // DRAW_AREA_H
