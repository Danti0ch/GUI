#include "drawable_objects.h"
#include "Vector3D.h"
#include "graphic_lib_wrapper.h"
#include "tests.h"
#include <math.h>
#include <assert.h>
#include <iostream>

static const double EPS = 1e-8;

static const uint WINDOW_HEIGHT = 720;
static const uint WINDOW_WIDTH  = 1080;

static const double   SPHERE_RADIUS = 50;
static const Vector3D BEHOLDER_VTOR(20, 40, 60);
static const double   AMBIENT_VAL        = 0.6;
static const uint     SPECULAR_POW_RATIO = 4;
static const double   LIGHT_Z_CT         = 60;

static const Color SPHERE_COLOR(255, 100, 0, 255);
static const Color LIGHT_COLOR(100, 123, 86, 255);

static const double DIFFUSE_RATIO   = 1.3;
static const double AMBIENT_RATIO   = 1.1;
static const double SPECULAR_RATIO  = 1.1;

//========================================================================================//

//                          PUBLIC_FUNCTIONS_DEFINITION

//========================================================================================//

SphereRender::SphereRender():GraphicSpace(WINDOW_WIDTH, WINDOW_HEIGHT),
    image_cts_(10, 710, 10, 710, -100, 100, -100, 100),
    manip_cts_(720, 920, 400, 600, -100, 100, -100, 100),
    x_manip_(30), y_manip_(30)
{
    Clear();
    manip_cts_.Draw(this, Color(0, 0, 0, 255));

    Vector click_vtor(x_manip_, y_manip_, VT_DATA::COORD);
    click_vtor.Draw(this, manip_cts_);
    draw_sphere();

    Show();
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

            Color cur_color = get_sphere_pixel_color(x_i, y_i);
            DrawPixel(x_i, y_i, cur_color);
        }
    }

    return;
}
//----------------------------------------------------------------------------------------//

#include <iostream>
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
        else{
            specular_val = pow(specular_val, SPECULAR_POW_RATIO);
        }
    }
    
    Color tmp_color    = SPHERE_COLOR * LIGHT_COLOR;
    Color result_color = tmp_color * diffuse_val * DIFFUSE_RATIO +
                         tmp_color * AMBIENT_RATIO +
                         LIGHT_COLOR * specular_val * SPECULAR_RATIO;

    result_color.a(255);
    return result_color;
}
//----------------------------------------------------------------------------------------//

void SphereRender::MouseButtonPressHandler(uint x_pos, uint y_pos){

    if(CheckCoordInCTS(manip_cts_, x_pos, y_pos)){

        x_manip_ = manip_cts_.CountAxisPosX(x_pos);
        y_manip_ = manip_cts_.CountAxisPosY(y_pos);
    }
    else if(CheckCoordInCTS(image_cts_, x_pos, y_pos)){
        
        x_manip_ = image_cts_.CountAxisPosX(x_pos);
        y_manip_ = image_cts_.CountAxisPosY(y_pos);
    }
    else return;

    Clear();
    manip_cts_.Draw(this, Color(0, 0, 0, 255));

    Vector click_vtor(x_manip_, y_manip_, VT_DATA::COORD);
    click_vtor.Draw(this, manip_cts_);
    draw_sphere();

    Show();

    return;
}
//----------------------------------------------------------------------------------------//
