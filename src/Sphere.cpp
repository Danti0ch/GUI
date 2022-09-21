#include "graphic_lib_wrapper.h"
#include "Raytracer.h"
#include <math.h>

Sphere::Sphere(double x0, double y0, double z0, double r, gglib::Color col):
    geom::Sphere(x0, y0, z0, r),
    col_(col)
{}

Sphere::Sphere(const geom::Vector3D& v, double r, gglib::Color col):
    geom::Sphere(v, r),
    col_(col)
{}
//----------------------------------------------------------------------------------------//

gglib::Color Sphere::GetColor(const geom::Vector3D& pt, const Camera& cam, const std::vector<Light>& lights) const{

    if(!CheckPointIn(pt)) return gglib::Color(255, 255, 255);

    geom::Vector3D beholder_to_point_vtor = cam.pos - pt;
    geom::Vector3D sphere_to_point_vtor   = pt - center();

    gglib::Color result_color(0, 0, 0);

    uint n_lights = lights.size();
    for(uint n_light = 0; n_light < n_lights; n_light++){

        geom::Vector3D light_to_point_vtor = lights[n_light].pos - pt;
        
        double cosA = geom::CountCosAngle(sphere_to_point_vtor, light_to_point_vtor);

        double diffuse_val  = 0;
        double specular_val = 0;

        if(cosA > geom::EPS){
            diffuse_val = cosA;

            sphere_to_point_vtor.ChangeLen(cosA * light_to_point_vtor.len());
            
            geom::Vector3D light_reflected_vtor = sphere_to_point_vtor * 2 - light_to_point_vtor;
            specular_val = geom::CountCosAngle(light_reflected_vtor, beholder_to_point_vtor);

            if(specular_val < geom::EPS) specular_val = 0;
            else{
                // TODO: optimize
                specular_val = pow(specular_val, SPECULAR_POW_RATIO);
            }
        }
        
        gglib::Color tmp_color = col_ * lights[n_light].col();


        // TODO: check correct 
        result_color += tmp_color * diffuse_val * DIFFUSE_RATIO +
                       tmp_color * AMBIENT_RATIO +
                       lights[n_light].col() * specular_val * SPECULAR_RATIO;
    }

    result_color.a(255);
    return result_color;
}
//----------------------------------------------------------------------------------------//
