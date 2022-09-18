#include "drawable_objects.h"
#include "Vector3D.h"
#include "graphic_lib_wrapper.h"
#include <math.h>
#include <assert.h>
#include <iostream>

static const double EPS = 1e-8;

static const uint WINDOW_HEIGHT = 720;
static const uint WINDOW_WIDTH  = 1080;

static const double   SPHERE_RADIUS = 50;
static const Vector3D BEHOLDER_VTOR(70, 70, 150);
static const double   AMBIENT_VAL        = 0.6;
static const uint     SPECULAR_POW_RATIO = 7;
static const double   LIGHT_Z_CT         = 120;

static const Color SPHERE_COLOR(217, 2, 49, 255);
static const Color LIGHT_COLOR(217, 206, 2, 255);

static const double DIFFUSE_RATIO   = 0.7;
static const double AMBIENT_RATIO   = 0.2;
static const double SPECULAR_RATIO  = 0.1;

static const double COLOR_DIV_RATIO = (double)1 / (double)256;

//========================================================================================//

//                          PUBLIC_FUNCTIONS_DEFINITION

//========================================================================================//

SphereRender::SphereRender(){

    space_ = GraphicSpace(WINDOW_WIDTH, WINDOW_HEIGHT);
    space_.SetMouseButtonPressEvent(button_pressed_event);
    space_.SetUpdateHandler(update_handler);
    
    image_cts_ = CoordinateSus(10, 710, 10, 710, -100, 100, -100, 100);
    manip_cts_ = CoordinateSus(720, 920, 400, 600, -100, 100, -100, 100);
}
//----------------------------------------------------------------------------------------//

SphereRender::Init(){

    draw_sphere(space_, image_cts_, 30, 30);
    space_.HandleEvents();

    return;
}
//----------------------------------------------------------------------------------------//

//========================================================================================//

//                          LOCAL_FUNCTIONS_DEFINITION

//========================================================================================//

void SphereRender::draw_sphere(){

    uint n_pixel = 0;

    uint y_min = image_cts_.y_upper_pixel();
    uint y_max = image_cts_.y_lower_pixel();
    uint x_min = image_cts_.x_lower_pixel();
    uint x_max = image_cts_.x_upper_pixel();
    
    for(uint y_i = y_min; y_i <= y_max ; y_i++){
        for(uint x_i = x_min; x_i <= x_max; x_i++){

            Color cur_color = get_sphere_pixel_color(image_cts_, x_i, y_i, x_manip_, y_manip_);
            space_.DrawPixel(x_i, y_i, cur_color);
        }
    }

    return;
}
//----------------------------------------------------------------------------------------//

// TODO: сделать внешней?
Color SphereRender::get_sphere_pixel_color(uint x_pix, uint y_pix){

    double x_real = image_cts_.CountAxisPosX(x_pix);
    double y_real = image_cts_.CountAxisPosY(y_pix);
    
    double z_real_quad = SPHERE_RADIUS * SPHERE_RADIUS - x_real * x_real - y_real * y_real;
    if(z_real_quad <= EPS) return Color(255, 255, 255, 255);

    double z_real = sqrt(z_real_quad);

    Vector3D to_point_vtor(x_real, y_real, z_real);
    Vector3D light_vtor(x_manip_, y_manip_, LIGHT_Z_CT);

    Vector3D light_to_point_vtor    = light_vtor - to_point_vtor;
    Vector3D beholder_to_point_vtor = BEHOLDER_VTOR - to_point_vtor;
    
    double cosA = CountCosAngle(to_point_vtor, light_to_point_vtor);

    double diffuse_val  = 0;
    double specular_val = 0;

    if(cosA > EPS){
        diffuse_val = cosA;

        to_point_vtor.ChangeLen(cosA * light_to_point_vtor.len());
        
        Vector3D light_reflected_vtor = to_point_vtor * 2 - light_to_point_vtor;
        specular_val = CountCosAngle(light_reflected_vtor, beholder_to_point_vtor);

        if(specular_val < EPS) specular_val = 0;
    }

    Color col;

    double lc_r = LIGHT_COLOR.r;
    double lc_g = LIGHT_COLOR.g;
    double lc_b = LIGHT_COLOR.b;
    double lc_a = LIGHT_COLOR.a;
    
    double mc_r = SPHERE_COLOR.r;
    double mc_g = SPHERE_COLOR.g;
    double mc_b = SPHERE_COLOR.b;
    double mc_a = SPHERE_COLOR.a;
    
    uint r_comp = (uint)(lc_r * mc_r * diffuse_val * COLOR_DIV_RATIO * DIFFUSE_RATIO + 
            lc_r * mc_r * AMBIENT_RATIO * COLOR_DIV_RATIO + 
            lc_r * specular_val * SPECULAR_RATIO);
    
    uint g_comp = (uint)(lc_g * mc_g * diffuse_val * COLOR_DIV_RATIO * DIFFUSE_RATIO + 
            lc_g * mc_g * AMBIENT_RATIO * COLOR_DIV_RATIO + 
            lc_g * specular_val * SPECULAR_RATIO);

    uint b_comp = (uint)(lc_b * mc_b * diffuse_val * COLOR_DIV_RATIO * DIFFUSE_RATIO + 
            lc_b * mc_b * AMBIENT_RATIO * COLOR_DIV_RATIO + 
            lc_b * specular_val * SPECULAR_RATIO);

    return Color(r_comp, g_comp, b_comp, 255);   
}
//----------------------------------------------------------------------------------------//

void SphereRender::mouse_press_event(GraphicSpace* space, int x_pos, int y_pos){

    assert(space != NULL);

    if(CheckCoordInCTS(manip_cts_, x_pos, y_pos)){

        manip_x_ = manip_cts_.CountAxisPosX(x_pos);
        manip_y_ = manip_cts_.CountAxisPosY(y_pos);
    }
    else if(CheckCoordInCTS(image_cts_, x_pos, y_pos)){
        
        manip_x_ = image_cts_.CountAxisPosX(x_pos);
        manip_y_ = image_cts_.CountAxisPosY(y_pos);
    }
    
    return;
}
//----------------------------------------------------------------------------------------//

void SphereRender::update_handler(GraphicSpace* space){

    assert(obj != NULL);
    // TODO:
    space_->Clean(Color(255, 255, 255, 255));

    manip_cts_.Draw(space, Color(0, 0, 0, 255));

    Vector click_vtor(manip_x_, manip_y_, VT_DATA::COORD);
    click_vtor.Draw(space, manip_cts_);

    return;
}
//----------------------------------------------------------------------------------------//
