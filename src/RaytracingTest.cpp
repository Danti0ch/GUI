#include "tests.h"
#include <assert.h>
#include <math.h>

const uint WINDOW_WIDTH  = 1024;
const uint WINDOW_HEIGHT = 720;

const double EPS = 1e-8;
const double step_movement = 0.5;

static const double   AMBIENT_VAL        = 0.6;
static const uint     SPECULAR_POW_RATIO = 3;

static const double DIFFUSE_RATIO   = 1.8;
static const double AMBIENT_RATIO   = 1.2;
static const double SPECULAR_RATIO  = 0.6;

//========================================================================================//

//                          LOCAL_FUNCTIONS_DECLARATION

//========================================================================================//

void draw_scene(SceneRaytracer* scene);
Color get_color(SceneRaytracer* scene, const Vector3D& dir, const Vector3D& base);

//========================================================================================//

//                          PUBLIC_FUNCTIONS_DEFINITION

//========================================================================================//

SceneRaytracer::SceneRaytracer():
    GraphicSpace(WINDOW_WIDTH, WINDOW_HEIGHT),
    sp1(-1, 0, -48, 10), sp1_col(255, 23, 55, 255),
    sp2(5, 1, -64, 4),   sp2_col(255, 255, 12, 255),
    sp3(15, 54, -90, 15), sp3_col(123, 21, 124, 255),
    base(0, 0, 0), base_dir(0, 0, -1),
    light(15, 15, -5), light_color(150, 54, 15, 255)
{
    draw_scene(this);
    Show();
}
//----------------------------------------------------------------------------------------//

void SceneRaytracer::KeyPressHandler(Key key){

    if(key == Key::W){
        base.y(base.y() + step_movement);
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

Color get_sphere_pixel_color(const SceneRaytracer* scene, const Vector3D& to_point_vtor, const Vector3D& vt, Color col){

    Vector3D light_to_point_vtor    = scene->light - to_point_vtor;
    Vector3D beholder_to_point_vtor = scene->base - to_point_vtor;
    
    double cosA = CountCosAngle(vt, light_to_point_vtor);

    double diffuse_val  = 0;
    double specular_val = 0;

    if(cosA > EPS){

        diffuse_val = cosA;
        
        Vector3D to_point_vtor_changed = vt;
        to_point_vtor_changed.ChangeLen(cosA * light_to_point_vtor.len());
        
        Vector3D light_reflected_vtor = to_point_vtor_changed * 2 - light_to_point_vtor;
        specular_val = CountCosAngle(light_reflected_vtor, beholder_to_point_vtor);

        if(specular_val < EPS) specular_val = 0;
        else{
            specular_val = pow(specular_val, SPECULAR_POW_RATIO);
        }
    }
    
    Color tmp_color    = col * scene->light_color;
    Color result_color = tmp_color * diffuse_val * DIFFUSE_RATIO +
                         tmp_color * AMBIENT_RATIO +
                         scene->light_color * specular_val * SPECULAR_RATIO;

    result_color.a(255);
    return result_color;
}
//----------------------------------------------------------------------------------------//

void draw_scene(SceneRaytracer* scene){

    uint width  = scene->sizeX();
    uint height = scene->sizeY();

    for(uint n_x_pixel = 0; n_x_pixel < width; n_x_pixel++){
        for(uint n_y_pixel = 0; n_y_pixel < height; n_y_pixel++){
            
            double x_dir = ( 2 * ((double)n_x_pixel / width) - 1) * width / height + scene->base_dir.x();
            double y_dir = ( 2 * ((double)n_y_pixel / height) - 1) + scene->base_dir.y();
            
            Vector3D dir(x_dir, y_dir, -1);

            Color cur_color = get_color(scene, dir, scene->base);
            scene->DrawPixel(n_x_pixel, n_y_pixel, cur_color);
        }
    }

    return;
}
//----------------------------------------------------------------------------------------//

static bool is_lower_len(double ratio, double new_val){

    if(!std::isnan(new_val)){
        if(!std::isnan(ratio)){
            if(new_val - ratio < EPS) return 1;
        }
        else return 1;
    }

    return 0;
}
//----------------------------------------------------------------------------------------//

Color get_color(SceneRaytracer* scene, const Vector3D& dir, const Vector3D& base){

    assert(scene != NULL);

    double ratio[3] = {};

    ratio[0] = GetIntersectionRatio(base, dir, scene->sp1);
    ratio[1] = GetIntersectionRatio(base, dir, scene->sp2);
    ratio[2] = GetIntersectionRatio(base, dir, scene->sp3);

    Color cur_col(255, 255, 255, 255);

    int best_len_id = -1;
    double tmp = NAN;

    if(is_lower_len(tmp, ratio[0])){
        best_len_id = 0;
        tmp = ratio[0];
    }
    if(is_lower_len(tmp, ratio[1])){
        best_len_id = 1;
        tmp = ratio[1];
    }
    if(is_lower_len(tmp, ratio[2])){
        best_len_id = 2;
    }

    if(best_len_id == -1) return cur_col;
    
    switch(best_len_id){
        case 0:{
            cur_col = get_sphere_pixel_color(scene, base + dir * ratio[0], base + dir * ratio[0] - Vector3D(scene->sp1.x0(), scene->sp1.y0(), scene->sp1.z0()), scene->sp1_col);
            break;
        }
        case 1:{
            cur_col = get_sphere_pixel_color(scene, base + dir * ratio[1], base + dir * ratio[1] - Vector3D(scene->sp2.x0(), scene->sp2.y0(), scene->sp2.z0()), scene->sp2_col);
            break;
        }
        case 2:{
            cur_col = get_sphere_pixel_color(scene, base + dir * ratio[2], base + dir * ratio[2] - Vector3D(scene->sp3.x0(), scene->sp3.y0(), scene->sp3.z0()), scene->sp3_col);
            break;
        }
    }

    return cur_col;
}
//----------------------------------------------------------------------------------------//
