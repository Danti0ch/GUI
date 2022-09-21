#include "Raytracer.h"
#include <assert.h>
#include <math.h>

const uint WINDOW_WIDTH  = 1024;
const uint WINDOW_HEIGHT = 720;

const double step_movement = 0.5;

//========================================================================================//

//                          LOCAL_FUNCTIONS_DECLARATION

//========================================================================================//

static void  draw_scene(SceneRaytracer* scene);
static gglib::Color get_color(SceneRaytracer* scene, const geom::Vector3D& dir);

//========================================================================================//

//                          PUBLIC_FUNCTIONS_DEFINITION

//========================================================================================//

SceneRaytracer::SceneRaytracer():
    GraphicSpace(WINDOW_WIDTH, WINDOW_HEIGHT),
    light_source(15, 15, -5,     gglib::Color(150, 54, 15, 255)),
    cam(0, 0, 0, 0, 0, -1),
    spheres({
        Sphere(-1, 0, -48, 10,   gglib::Color(255, 23, 55, 255)),
        Sphere(5, 1, -64, 4,     gglib::Color(255, 255, 12, 255)),
        Sphere(15, 54, -90, 15, gglib::Color(123, 21, 124, 255))
    })
{
    draw_scene(this);
    Show();
}
//----------------------------------------------------------------------------------------//

void SceneRaytracer::KeyPressHandler(gglib::Key key){

    /*
    if(key == Key::W){
        cam.y(cam.y() + step_movement);
    }
    else if(key == Key::S){
        base.y(base.y() - step_movement);
    }
    else if(key == Key::A){
        base.x(base.x() - step_movement);
    }
    else if(key == Key::D){
        base.x(base.x() + step_movement);
    }
    else if(key == Key::F){
        base.z(base.z() - step_movement);
    }
    else if(key == Key::G){
        base.z(base.z() + step_movement);
    }
    else if(key == Key::Q){
        base_dir.x(base_dir.x() - step_movement);
    }
    else if(key == Key::E){
        base_dir.x(base_dir.x() + step_movement);
    }
    */
    
    return;
}
//----------------------------------------------------------------------------------------//

void SceneRaytracer::UpdateAfterEvents(){

    Clear();
    draw_scene(this);

    Show();
    return;
}
//----------------------------------------------------------------------------------------//

//========================================================================================//

//                          LOCAL_FUNCTIONS_DEFINITION

//========================================================================================//

static void  draw_scene(SceneRaytracer* scene){

    uint width  = scene->sizeX();
    uint height = scene->sizeY();

    for(uint n_x_pixel = 0; n_x_pixel < width; n_x_pixel++){
        for(uint n_y_pixel = 0; n_y_pixel < height; n_y_pixel++){
            
            double x_dir = ( 2 * ((double)n_x_pixel / width) - 1) * width / height;
            double y_dir = ( 2 * ((double)n_y_pixel / height) - 1);
            
            geom::Vector3D dir(x_dir, y_dir, -1);

            gglib::Color cur_color = get_color(scene, dir);
            scene->DrawPixel(n_x_pixel, n_y_pixel, cur_color);
        }
    }

    return;
}
//----------------------------------------------------------------------------------------//

static bool is_lower_dist(double ratio, double new_val){

    if(!std::isnan(new_val)){
        if(!std::isnan(ratio)){
            if(new_val - ratio < geom::EPS) return 1;
        }
        else return 1;
    }

    return 0;
}
//----------------------------------------------------------------------------------------//

#include <iostream>
static gglib::Color get_color(SceneRaytracer* scene, const geom::Vector3D& dir){

    assert(scene != NULL);
    
    uint n_spheres = sizeof(scene->spheres) / sizeof(Sphere);

    double ratio[n_spheres] = {};
    int smallest_dist_id    = -1;
    double smallest_ratio   = NAN;

    for(uint n_sphere = 0; n_sphere < n_spheres; n_sphere++){
        ratio[n_sphere] = geom::GetIntersectionRatio(scene->cam.pos, dir, scene->spheres[n_sphere]);

        if(is_lower_dist(smallest_ratio, ratio[n_sphere])){
            smallest_ratio = ratio[n_sphere];
            smallest_dist_id = n_sphere;
        }
    }

    if(smallest_dist_id == -1) return gglib::Color(255, 255, 255);
    
    geom::Vector3D pt = scene->cam.pos + dir * smallest_ratio;

    return scene->spheres[smallest_dist_id].GetColor(pt, scene->cam, {scene->light_source});
}
//----------------------------------------------------------------------------------------//
