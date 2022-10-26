#include "Raytracer.h"
#include "logger.h"

const double step_movement          = 0.5;
const int    LIGHT_REFLECTION_DEPTH = 4;
const int    LIGHT_INTENCITY_VAL    = 20;

const double PLANE_INTERSEC_UPPER_LIM = 1e20;
const double CosBrusterAngle          = 0.02;
const double CAM_STEP_VAL             = 0.5;

const uint   SSAA_X_RATIO             = 2;
const uint   SSAA_Y_RATIO             = 2;
const double SSAA_COL_RATIO           = (double)1/((double)SSAA_X_RATIO * SSAA_Y_RATIO);

//========================================================================================//

//                          LOCAL_FUNCTIONS_DECLARATION

//========================================================================================//

static Color cast_ray(Raytracer* scene, const geom::Vector3D& base, const geom::Vector3D& dir, uint depth);
static bool             get_ray_interection(Raytracer* scene, const geom::Vector3D& base, const geom::Vector3D& dir, geom::Vector3D* pt = NULL, geom::Vector3D* norm = NULL, Material* mat = NULL);
static geom::Vector3D   get_reflected_vector(const geom::Vector3D& pt, const geom::Vector3D& norm);
static geom::Vector3D   get_refracted_vector(const geom::Vector3D& pt,   const geom::Vector3D& norm, double refact_coef1, double refact_coef2 = 1);
static bool is_lower_dist(double ratio, double new_val);

//========================================================================================//

//                          PUBLIC_FUNCTIONS_DEFINITION

//========================================================================================//

Raytracer::Raytracer(ContainerWidget* parent_widget, uint x, uint y, uint width, uint height):
    Widget(parent_widget, x, y, width, height),
    light_sources_(),
    shapes_(),
    background_col_(135, 206, 235),
    cam_(0, 0, 0, 0, 0, -1)
{
    shapes_.push_back(new Sphere(1.5,      -0.5,  -13, 3,  SteelMaterial));
    shapes_.push_back(new Sphere(-3, 0, -11, 2,            TreeMaterial));
    shapes_.push_back(new Sphere(7,       5, -14, 4,       MirrorMaterial));
    shapes_.push_back(new Sphere(-1,   -1.5,  -7, 2,       GlassMaterial));
    
    light_sources_.push_back(SphereLight(-10, 10, 10    , Color(255, 211, 95, 255)));
}
//----------------------------------------------------------------------------------------//


void Raytracer::draw(GraphicSpace* space){

    uint ssaa_width  = width() * SSAA_X_RATIO;
    uint ssaa_height = height() * SSAA_Y_RATIO;

    for(uint n_x_pixel = 0; n_x_pixel < width(); n_x_pixel++){
        for(uint n_y_pixel = 0; n_y_pixel < height(); n_y_pixel++){
            
            // TODO: refactor
            double r = 0, g = 0, b = 0, a = 0;
            for(uint x_loc = 0; x_loc < SSAA_X_RATIO; x_loc++){
                for(uint y_loc = 0; y_loc < SSAA_Y_RATIO; y_loc++){
                    double x_dir = ( 2 * ((double)(n_x_pixel * SSAA_X_RATIO + x_loc) / (double)ssaa_width) - 1) * (double)ssaa_width / (double)ssaa_height * tan(cam_.view_angle() / 2);
                    double y_dir = ( 2 * ((double)(n_y_pixel * SSAA_Y_RATIO + y_loc) / (double)ssaa_height) - 1) * tan(cam_.view_angle() / 2);
                    
                    geom::Vector3D dir(x_dir, y_dir, 0);
                    dir += cam_.dir();

                    Color col = cast_ray(this, cam_.pos(), dir, LIGHT_REFLECTION_DEPTH);
                    r += col.r(); g += col.g(); b += col.b(); a += col.a();
                }
            }

            Color cur_color((uint)(r/4), (uint)(g/4), (uint)(b/4), 255);
            space->drawPixel(n_x_pixel, n_y_pixel, cur_color);
        }
    }
    return;
}
//----------------------------------------------------------------------------------------//

//========================================================================================//

//                          LOCAL_FUNCTIONS_DEFINITION

//========================================================================================//

static Color cast_ray(Raytracer* scene, const geom::Vector3D& base, const geom::Vector3D& dir, uint depth){
    NASSERT(scene);

    if(depth == 0){
        return scene->background_col();
    }

    geom::Vector3D pt, norm;
    Material cur_mat = TreeMaterial;
    
    bool is_intersection = get_ray_interection(scene, base, dir, &pt, &norm, &cur_mat);
    if(!is_intersection) return scene->background_col();

    #if CONTOUR_ENABLED
        if(fabs(CountCosAngle(pt, norm)) < 0.22){
            return Color(0, 0, 0, 255);
        }
    #endif // CONTOUR_ENABLED

    Color reflected_col(0, 0, 0, 0), refracted_col(0, 0, 0, 0);

    if(cur_mat.koef[REFLECT] > geom::EPS){
        geom::Vector3D reflect_dir = get_reflected_vector(dir, norm);
        reflected_col = cast_ray(scene, pt, reflect_dir, depth - 1);
    }

    if(cur_mat.koef[REFRACT] > geom::EPS){

        geom::Vector3D refract_dir = get_refracted_vector(dir, -norm, cur_mat.refract_ratio);
        refracted_col = cast_ray(scene, pt, refract_dir, depth - 1);
    }

    geom::Vector3D beholder_to_point_vtor = scene->cam().pos() - pt;
    Color result_color(0, 0, 0);
    uint n_lights = scene->light_sources().size();

    Color diffuse_color(0, 0, 0);
    Color spec_color(0, 0, 0);
    Color ambient_col(0, 0, 0);

    for(uint n_light = 0; n_light < n_lights; n_light++){

        geom::Vector3D light_to_point_vtor = scene->light_sources()[n_light].pos() - pt;

        double cosA = geom::CountCosAngle(norm, light_to_point_vtor);

        double diffuse_val  = 0;
        double specular_val = 0;

        bool is_interect = get_ray_interection(scene, pt, scene->light_sources()[n_light].pos() - pt);
    
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
        ambient_col   += cur_mat.col *  scene->light_sources()[n_light].col() * intensity_coef;
        spec_color    += scene->light_sources()[n_light].col() * specular_val * intensity_coef;
        diffuse_color += cur_mat.col * scene->light_sources()[n_light].col() * diffuse_val * intensity_coef;
    }

    Color res_col = 
           diffuse_color * cur_mat.koef[DIFFUSE]  +
           reflected_col * cur_mat.koef[REFLECT]  +
           refracted_col * cur_mat.koef[REFRACT]  + 
           spec_color    * cur_mat.koef[SPECULAR] +
           ambient_col   * cur_mat.koef[AMBIENT];
    
    return res_col;
}
//----------------------------------------------------------------------------------------//

static bool get_ray_interection(Raytracer* scene, const geom::Vector3D& base, const geom::Vector3D& dir, geom::Vector3D* pt, geom::Vector3D* norm, Material* mat){

    NASSERT(scene);

    int      n_required_shape  = -1;
    double   smallest_ratio    = NAN;

    for(uint n_shape = 0; n_shape < scene->shapes().size(); n_shape++){
        double cur_ratio = scene->shapes()[n_shape]->GetIntersectionRatio(base, dir);

        if(is_lower_dist(smallest_ratio, cur_ratio)){
            smallest_ratio    = cur_ratio;
            n_required_shape = n_shape;
        }
    }
    if(n_required_shape == -1) return false;

    if(!ISNULL(pt))    *pt   = base + dir * smallest_ratio;
    if(!ISNULL(mat))   *mat  = scene->shapes()[n_required_shape]->mat();
    if(!ISNULL(norm))  *norm = scene->shapes()[n_required_shape]->GetNormal(*pt);

    return true;
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
