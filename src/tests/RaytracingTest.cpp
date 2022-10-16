#include "Raytracer.h"
#include <assert.h>
#include <math.h>
#include "logger.h"

const double step_movement          = 0.5;
const int    LIGHT_REFLECTION_DEPTH = 4;
const int    LIGHT_INTENCITY_VAL    = 20;

const double PLANE_INTERSEC_UPPER_LIM = 1e20;
const double CosBrusterAngle          = 0.02;
const double CAM_STEP_VAL             = 0.5;

//========================================================================================//

//                          LOCAL_FUNCTIONS_DECLARATION

//========================================================================================//

static void             draw_scene(SceneRaytracer* scene);
static gglib::Color     cast_ray(SceneRaytracer* scene, const geom::Vector3D& base, const geom::Vector3D& dir,uint depth);
static geom::Vector3D   get_reflected_vector(const geom::Vector3D& pt, const geom::Vector3D& norm);
static geom::Vector3D   get_refracted_vector(const geom::Vector3D& pt,   const geom::Vector3D& norm, double refact_coef1, double refact_coef2 = 1);
static bool             get_ray_interection(const SceneRaytracer* scene, const geom::Vector3D& base, const geom::Vector3D& dir, geom::Vector3D* pt = NULL, geom::Vector3D* norm = NULL, Material* mat = NULL);

//========================================================================================//

//                          PUBLIC_FUNCTIONS_DEFINITION

//========================================================================================//

SceneRaytracer::SceneRaytracer():
    GraphicSpace(1024, 720),
    background_col(135, 206, 235),
    light_sources(1, SphereLight()),
    cam(0, 0, 0, 0, 0, -1),
    shapes(N_SHAPES, NULL)
{
    LogInit("..");

    shapes[0] = new Sphere(1.5,      -0.5,  -13, 3,  SteelMaterial);
    shapes[1] = new Sphere(-3, 0, -11, 2,            TreeMaterial);
    shapes[2] = new Sphere(7,       5, -14, 4,       MirrorMaterial);
    shapes[3] = new Sphere(-1,   -1.5,  -7, 2,       GlassMaterial);
    shapes[4] = new Plane(geom::Vector3D(0, -4, 0), geom::Vector3D(0, -1, 0), GrassMaterial);

    light_sources[0] = SphereLight(-10, 10, 10    , gglib::Color(255, 211, 95, 255));

    DLOG(INFO, "Shapes initialized\n");
    draw_scene(this);
    Show();
}
//----------------------------------------------------------------------------------------//

SceneRaytracer::~SceneRaytracer(){

    for(uint n_shape = 0; n_shape < N_SHAPES; n_shape++){
        delete shapes[n_shape];
    }
    LogClose();
}
//----------------------------------------------------------------------------------------//

void SceneRaytracer::KeyPressHandler(gglib::Key key){

    if(key == gglib::Key::W){
        cam.pos().y(cam.pos().y() + CAM_STEP_VAL);
    }
    else if(key == gglib::Key::S){
        cam.pos().y(cam.pos().y() - CAM_STEP_VAL);
    }
    else if(key == gglib::Key::A){
        cam.pos().x(cam.pos().x() - CAM_STEP_VAL);
    }
    else if(key == gglib::Key::D){
        cam.pos().x(cam.pos().x() + CAM_STEP_VAL);
    }
    else if(key == gglib::Key::F){
        cam.pos() += cam.dir() * CAM_STEP_VAL;
    }
    else if(key == gglib::Key::G){
        cam.pos() -= cam.dir() * CAM_STEP_VAL;
    }
    else if(key == gglib::Key::Q){
        cam.dir().x(cam.dir().x() - CAM_STEP_VAL);
    }
    else if(key == gglib::Key::E){
        cam.dir().x(cam.dir().x() + CAM_STEP_VAL);
    }

    return;
}
//----------------------------------------------------------------------------------------//

void SceneRaytracer::UpdateAfterEvents(){

    Clear();
    draw_scene(this);
    std::cout << "Drawn\n";

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

    MDLOG("Scene parameters:\n"
                    "\theight: %d\n"
                    "\twidth:  %d\n"
                    "ray_base: (%g, %g, %g)\n", 
            height, width, scene->cam.pos().x(), scene->cam.pos().y(), scene->cam.pos().z());
            std::cout << scene->cam.pos() << "\n";
    
    for(uint n_x_pixel = 0; n_x_pixel < width; n_x_pixel++){
        for(uint n_y_pixel = 0; n_y_pixel < height; n_y_pixel++){
            
            double x_dir = ( 2 * ((double)n_x_pixel / width) - 1) * width / height * tan(scene->cam.view_angle() / 2);
            double y_dir = ( 2 * ((double)n_y_pixel / height) - 1) * tan(scene->cam.view_angle() / 2);
            
            geom::Vector3D dir(x_dir, y_dir, 0);
            dir += scene->cam.dir();

            MDLOG("Throwing ray (%g, %g, %g)\n", dir.x(), dir.y(), dir.z());

            gglib::Color cur_color = cast_ray(scene, scene->cam.pos(), dir, LIGHT_REFLECTION_DEPTH);
            MDLOG("Got color (%u, %u, %u, %u)\n", cur_color.r(), cur_color.g(), cur_color.b(), cur_color.a());
            scene->DrawPixel(n_x_pixel, n_y_pixel, cur_color);
        }
    }

    MDLOG("Scene rendering completed\n");
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

    NASSERT(scene);

    int      n_required_shape  = -1;
    double   smallest_ratio    = NAN;
    MDLOG("attempt to get intersection for (%g + %gt, %g + %gt, %g + %gt)", 
                    base.x(), dir.x(), base.y(), dir.y(), base.z(), dir.z());
                
    for(uint n_shape = 0; n_shape < N_SHAPES; n_shape++){
        double cur_ratio = scene->shapes[n_shape]->GetIntersectionRatio(base, dir);

        if(is_lower_dist(smallest_ratio, cur_ratio)){
            smallest_ratio    = cur_ratio;
            n_required_shape = n_shape;
        }
    }

    if(n_required_shape == -1){
        
        MDLOG("\tFAILED\n")
        return false;
    }
    MDLOG("\tSUCCESS!\n"
          "n_shape: %u\n"
          "ratio:   %g\n"
          "pt:      (%g, %g, %g)",
                n_required_shape, smallest_ratio, base.x() + dir.x() * smallest_ratio, base.y() + dir.y() * smallest_ratio, base.z() + dir.z() * smallest_ratio);
    
    if(!ISNULL(pt))    *pt   = base + dir * smallest_ratio;
    if(!ISNULL(mat))   *mat  = scene->shapes[n_required_shape]->mat();
    if(!ISNULL(norm)){
        *norm = scene->shapes[n_required_shape]->GetNormal(*pt);
        MDLOG("norm:    (%g, %g, %g)\n", norm->x(), norm->y(), norm->z());
    }

    return true;
}
//----------------------------------------------------------------------------------------//

static gglib::Color cast_ray(SceneRaytracer* scene, const geom::Vector3D& base, const geom::Vector3D& dir, uint depth){

    NASSERT(scene);

    if(depth == 0){
        MDLOG("casting completed\n");
        return scene->background_col;
    }

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
        geom::Vector3D reflect_dir = get_reflected_vector(dir, norm);
        reflected_col = cast_ray(scene, pt, reflect_dir, depth - 1);
    }

    if(cur_mat.koef[REFRACT] > geom::EPS){

        geom::Vector3D refract_dir = get_refracted_vector(dir, -norm, cur_mat.refract_ratio);
        refracted_col = cast_ray(scene, pt, refract_dir, depth - 1);
    }

    geom::Vector3D beholder_to_point_vtor = scene->cam.pos() - pt;
    gglib::Color result_color(0, 0, 0);
    uint n_lights = scene->light_sources.size();

    gglib::Color diffuse_color(0, 0, 0);
    gglib::Color spec_color(0, 0, 0);
    gglib::Color ambient_col(0, 0, 0);

    for(uint n_light = 0; n_light < n_lights; n_light++){

        geom::Vector3D light_to_point_vtor = scene->light_sources[n_light].pos() - pt;

        double cosA = geom::CountCosAngle(norm, light_to_point_vtor);

        double diffuse_val  = 0;
        double specular_val = 0;

        bool is_interect = get_ray_interection(scene, pt, scene->light_sources[n_light].pos() - pt);
    
        if(cosA > geom::EPS && !is_interect){
            diffuse_val = cosA;

            geom::Vector3D light_reflected_vtor = get_reflected_vector(-light_to_point_vtor, norm);
            
            specular_val = geom::CountCosAngle(light_reflected_vtor, beholder_to_point_vtor);

            if(specular_val < geom::EPS) specular_val = 0;
            else{
                // TODO: optimize
                specular_val = pow(specular_val, cur_mat.shininess_ratio);
            }
        }

        double intensity_coef = LIGHT_INTENCITY_VAL / light_to_point_vtor.len();
        ambient_col   += cur_mat.col *  scene->light_sources[n_light].col() * intensity_coef;
        spec_color    += scene->light_sources[n_light].col() * specular_val * intensity_coef;
        diffuse_color += cur_mat.col * scene->light_sources[n_light].col() * diffuse_val * intensity_coef;
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

geom::Vector3D get_reflected_vector(const geom::Vector3D& pt, const geom::Vector3D& norm){

    geom::Vector3D norm_normalized = norm;
    norm_normalized.Normalize();

//    if(scalar < geom::EPS) return geom::Vector3D(0, 0, 0);

    return pt - norm_normalized * 2 * CountScalarMul(pt, norm_normalized);
}
//----------------------------------------------------------------------------------------//

geom::Vector3D get_refracted_vector(const geom::Vector3D& pt, const geom::Vector3D& norm, double refact_coef1, double refact_coef2){

    double cosA = geom::CountCosAngle(pt, norm);

    if(cosA < 0){
        return get_refracted_vector(pt, -norm, refact_coef2, refact_coef1);
    }   

    if(cosA < CosBrusterAngle){
        return get_reflected_vector(pt, norm);
    }

    double d2   = refact_coef2 / refact_coef1;
    double cosB = 1 - d2 * d2 * (1 - cosA * cosA);

    geom::Vector3D n = norm;
    n.Normalize();

    geom::Vector3D p = pt;
    p.Normalize();

    if(cosB < 0) return geom::Vector3D(0, 0, 0);

    return p * d2 + n * (-d2 * cosA + sqrt(cosB));
}
//----------------------------------------------------------------------------------------//
