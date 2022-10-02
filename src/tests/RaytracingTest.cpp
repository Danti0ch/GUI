#include "Raytracer.h"
#include <assert.h>
#include <math.h>

const double step_movement          = 0.5;
const int    LIGHT_REFLECTION_DEPTH = 4;
const int    LIGHT_INTENCITY_VAL    = 5;

const double PLANE_INTERSEC_UPPER_LIM = 50;

//========================================================================================//

//                          LOCAL_FUNCTIONS_DECLARATION

//========================================================================================//

static void             draw_scene(SceneRaytracer* scene);
static gglib::Color     cast_ray(SceneRaytracer* scene, const geom::Vector3D& base, const geom::Vector3D& dir,uint depth, double intensity);
static geom::Vector3D   get_reflected_vector(const geom::Vector3D& pt, const geom::Sphere& obj);
static geom::Vector3D   get_refracted_vector(const geom::Vector3D& pt,   const geom::Vector3D& norm, double refact_coef1, double refact_coef2 = 1);
static bool             get_ray_interection(const SceneRaytracer* scene, const geom::Vector3D& base, const geom::Vector3D& dir, geom::Vector3D* pt = NULL, geom::Vector3D* norm = NULL, Material* mat = NULL);

//========================================================================================//

//                          PUBLIC_FUNCTIONS_DEFINITION

//========================================================================================//

SceneRaytracer::SceneRaytracer():
    GraphicSpace(1024, 720),
    background_col(135, 206, 235),
    light_source({
        SphereLight(3, 2, -3, gglib::Color(255, 211, 95, 255))
    }),
    cam(0, 0, 0, 0, 0, -1),
    spheres({
        Sphere(-3,      0,  -6, 2,  SteelMaterial),
        Sphere(-1.5, -0.5, -14, 3,  TreeMaterial),
        Sphere(7,       2, -24, 4,  MirrorMaterial),
        Sphere(-1,   -1.5,  -5, 2,  GlassMaterial)
    }),
    planes({
        Plane(geom::Vector3D(0, -4, 0), geom::Vector3D(0, -1, 0), SteelMaterial),
        //Plane(geom::Vector3D(-15,  0, 0), geom::Vector3D(1, 0, 0), SteelMaterial),
        //Plane(geom::Vector3D(15,  0, 0), geom::Vector3D(1, 0, 0), SteelMaterial)  
    })
{
    draw_scene(this);
    Show();
}
//----------------------------------------------------------------------------------------//

void SceneRaytracer::KeyPressHandler(gglib::Key key){

    /*
    if(key == gglib::Key::W){
        cam.pos.y(cam.pos.y() + 0.4);
    }
    else if(key == gglib::Key::S){
        cam.pos.y(cam.pos.y() - 0.4);
    }
    else if(key == gglib::Key::A){
        cam.pos.x(cam.pos.x() - 0.4);
    }
    else if(key == gglib::Key::D){
        cam.pos.x(cam.pos.x() + 0.4);
    }
    else if(key == gglib::Key::F){
        cam.pos.z(cam.pos.z() - 0.4);
    }
    else if(key == gglib::Key::G){
        cam.pos.z(cam.pos.z() + 0.4);
    }
    else if(key == gglib::Key::Q){
        cam.dir.x(cam.dir.x() - 0.4);
    }
    else if(key == gglib::Key::E){
        cam.dir.x(cam.dir.x() + 0.4);
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

static void draw_scene(SceneRaytracer* scene){

    uint width  = scene->sizeX();
    uint height = scene->sizeY();

    for(uint n_x_pixel = 0; n_x_pixel < width; n_x_pixel++){
        for(uint n_y_pixel = 0; n_y_pixel < height; n_y_pixel++){
            
            // TODO: make angle
            double x_dir = ( 2 * ((double)n_x_pixel / width) - 1) * width / height;
            double y_dir = ( 2 * ((double)n_y_pixel / height) - 1);
            
            // TODO: make smart camera view dir
            geom::Vector3D dir(x_dir, y_dir, -1);

            gglib::Color cur_color = cast_ray(scene, scene->cam.pos(), dir, LIGHT_REFLECTION_DEPTH, LIGHT_INTENCITY_VAL);
            scene->DrawPixel(n_x_pixel, n_y_pixel, cur_color);
        }
    }

    return;
}
//----------------------------------------------------------------------------------------//

static bool is_lower_dist(double ratio, double new_val){

    if(new_val < geom::EPS) return 0;

    if(!std::isnan(new_val)){
        if(!std::isnan(ratio)){
            if(new_val - ratio < geom::EPS) return 1;
        }
        else return 1;
    }

    return 0;
}
//----------------------------------------------------------------------------------------//

static bool get_ray_interection(const SceneRaytracer* scene, const geom::Vector3D& base, const geom::Vector3D& dir, geom::Vector3D* pt, geom::Vector3D* norm, Material* mat){

    assert(scene != NULL);

    uint  n_spheres = sizeof(scene->spheres) / sizeof(Sphere);

    int      n_required_shape  = -1;
    double   smallest_ratio    = NAN;

    double cur_n_required_shape  = -1;
    double cur_smallest_ratio    = NAN;

    SHAPE_ID shape_type        = SHAPE_ID::WRONG;

    for(uint n_sphere = 0; n_sphere < n_spheres; n_sphere++){
        double cur_ratio = GetIntersectionRatio(base, dir, scene->spheres[n_sphere]);

        if(is_lower_dist(cur_smallest_ratio, cur_ratio)){
            cur_smallest_ratio    = cur_ratio;
            cur_n_required_shape = n_sphere;
        }
    }

    if(cur_n_required_shape != -1){
        
        n_required_shape = cur_n_required_shape;
        smallest_ratio   = cur_smallest_ratio;
        shape_type       = SHAPE_ID::SPHERE;
    }

    cur_n_required_shape  = -1;
    cur_smallest_ratio    = NAN;

    uint  n_planes = sizeof(scene->planes) / sizeof(Plane);

    for(uint n_plane = 0; n_plane < n_planes; n_plane++){
        double cur_ratio = GetIntersectionRatio(base, dir, scene->planes[n_plane]);

        if(cur_ratio < PLANE_INTERSEC_UPPER_LIM && is_lower_dist(cur_smallest_ratio, cur_ratio)){
            cur_smallest_ratio    = cur_ratio;
            cur_n_required_shape = n_plane;
        }
    }

    if(cur_n_required_shape != -1 && is_lower_dist(smallest_ratio, cur_smallest_ratio)){
        
        n_required_shape = cur_n_required_shape;
        smallest_ratio   = cur_smallest_ratio;
        shape_type       = SHAPE_ID::PLANE;
    }

    if(n_required_shape == -1) return false;

    if(pt != NULL){
        *pt = base + dir * smallest_ratio;
    }

    if(norm != NULL){

        switch((int)shape_type){
            case (int)SHAPE_ID::SPHERE:{
                *norm = *pt - scene->spheres[n_required_shape].center();
                break;
            }
            case (int)SHAPE_ID::PLANE:{
                *norm = scene->planes[n_required_shape].GetNormal(*pt);
                break;
            }               
        }
    }

    if(mat != NULL){
        switch((int)shape_type){
            case (int)SHAPE_ID::SPHERE:{
                *mat = scene->spheres[n_required_shape].mat();
                break;
            }
            case (int)SHAPE_ID::PLANE:{
                *mat = scene->planes[n_required_shape].mat();
                break;
            }               
        }
    }
    return true;
}
//----------------------------------------------------------------------------------------//

static gglib::Color cast_ray(SceneRaytracer* scene, const geom::Vector3D& base, const geom::Vector3D& dir, uint depth, double intensity){

    assert(scene != NULL);

    if(depth == 0) return scene->background_col;
    if(intensity < geom::EPS) return gglib::Color(0, 0, 0);

    geom::Vector3D pt, norm;
    Material cur_mat = TreeMaterial;
    
    bool is_intersection = get_ray_interection(scene, base, dir, &pt, &norm, &cur_mat);

    if(!is_intersection) return scene->background_col;

    #if CONTOUR_ENABLED
        if(fabs(CountCosAngle(pt, norm)) < 0.22){
            return gglib::Color(0, 0, 0, 255);
        }
    #endif // CONTOUR_ENABLED

    gglib::Color reflected_col(0, 0, 0, 0), refracted_col(0, 0, 0, 0);

    if(cur_mat.koef[REFLECT] > geom::EPS){
        geom::Vector3D reflect_dir = GetReflectedVector(-pt, norm);
        reflected_col = cast_ray(scene, pt, reflect_dir, depth - 1, intensity);
    }

    if(cur_mat.koef[REFRACT] > geom::EPS){
        geom::Vector3D refract_dir = get_refracted_vector(pt, norm, cur_mat.refract_ratio);
        refracted_col = cast_ray(scene, pt, refract_dir, depth, intensity);
    }

    geom::Vector3D beholder_to_point_vtor = scene->cam.pos() - pt;
    gglib::Color result_color(0, 0, 0);
    uint n_lights = sizeof(scene->light_source) / sizeof(SphereLight);

    gglib::Color diffuse_color(0, 0, 0);
    gglib::Color spec_color(0, 0, 0);
    gglib::Color ambient_col(0, 0, 0);

    for(uint n_light = 0; n_light < n_lights; n_light++){

        geom::Vector3D light_to_point_vtor = scene->light_source[n_light].pos() - pt;

        double cosA = geom::CountCosAngle(norm, light_to_point_vtor);

        double diffuse_val  = 0;
        double specular_val = 0;

        bool is_interect = get_ray_interection(scene, pt, scene->light_source[n_light].pos() - pt);
    
        if(cosA > geom::EPS && !is_interect){
            diffuse_val = cosA;

            geom::Vector3D light_reflected_vtor = GetReflectedVector(light_to_point_vtor, norm);
            
            specular_val = geom::CountCosAngle(light_reflected_vtor, beholder_to_point_vtor);

            if(specular_val < geom::EPS) specular_val = 0;
            else{
                // TODO: optimize
                specular_val = pow(specular_val, cur_mat.shininess_ratio);
            }
        }

        double intensity_coef = intensity / light_to_point_vtor.len();
        ambient_col   += cur_mat.col *  scene->light_source[n_light].col() * intensity_coef;
        spec_color    += scene->light_source[n_light].col() * specular_val * intensity_coef;
        diffuse_color += cur_mat.col * scene->light_source[n_light].col() * diffuse_val * intensity_coef;
    }

    gglib::Color res_col = 
           diffuse_color * cur_mat.koef[DIFFUSE]  +
           reflected_col * cur_mat.koef[REFLECT]  +
           refracted_col * cur_mat.koef[REFRACT]  + 
           spec_color    * cur_mat.koef[SPECULAR] +
           ambient_col   * cur_mat.koef[AMBIENT];
    
    return res_col;
}
//----------------------------------------------------------------------------------------//

geom::Vector3D GetReflectedVector(const geom::Vector3D& pt, const geom::Vector3D& norm){

    double scalar = CountScalarMul(pt, norm);

    if(scalar < geom::EPS) return geom::Vector3D(0, 0, 0);

    return pt + norm * 2 * (scalar) / norm.len();
}
//----------------------------------------------------------------------------------------//

geom::Vector3D GetReflectedVector(const geom::Vector3D& pt, const geom::Sphere& obj){

    geom::Vector3D norm = pt - obj.center();
    return GetReflectedVector(pt, norm);
}
//----------------------------------------------------------------------------------------//

geom::Vector3D GetReflectedVector(const geom::Vector3D& pt, const geom::Plane& obj){

    geom::Vector3D norm = obj.GetNormal(pt);
    if(CountScalarMul(pt, norm) > geom::EPS){
        return GetReflectedVector(pt, norm);
    }
    return GetReflectedVector(pt, -norm);
}
//----------------------------------------------------------------------------------------//

geom::Vector3D get_refracted_vector(const geom::Vector3D& pt, const geom::Vector3D& norm, double refact_coef1, double refact_coef2){

    double cosA = geom::CountCosAngle(pt, norm);

    if(cosA < geom::EPS){
        return get_refracted_vector(pt, -norm, refact_coef1, refact_coef2);
    }

    double d2   = refact_coef2 / refact_coef1;

    double cosB = sqrt(1 - d2 * sqrt(1 - cosA * cosA));
    double d1   = cosA / cosB;
        
    return pt * (d1 * d2) + norm * pt.len() / norm.len() * cosA * (1 - d1 * d2);
}
//----------------------------------------------------------------------------------------//
