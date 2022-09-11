#include "drawer.h"
#include <math.h>
#include <assert.h>
#include <iostream>

static const double EPS = 1e-8;

static const uint WINDOW_HEIGHT = 720;
static const uint WINDOW_WIDTH  = 1080;

static const double CTS1_CT_X_INIT = 1;
static const double CTS1_CT_Y_INIT = 1;

static const double   SPHERE_RADIUS = 50;
static const Vector3D BEHOLDER_VTOR(40, 40, 90);
static const Vector3D LIGHT_VTOR(30, 30, 90);
static const double   AMBIENT_VAL      = 0.5;
static const uint     SPECULAR_POW_RATIO = 7;

static const sf::Color SPHERE_COLOR(168, 253, 80, 255);
static const sf::Color LIGHT_COLOR(168, 74, 80, 255);

static const double DIFFUSE_RATIO   = 0.6;
static const double AMBIENT_RATIO   = 0.1;
static const double SPECULAR_RATIO  = 0.3;
static const double COLOR_DIV_RATIO = 1 / 256;
 
static const double TIME_VECTOR_LEN = 6;

/*
const uint N_X_GRAPHS = 11;
const uint N_Y_GRAPHS = 12;

const uint N_X_SIZE = WINDOW_WIDTH / N_X_GRAPHS;
const uint N_Y_SIZE = WINDOW_HEIGHT / N_Y_GRAPHS;
*/
//========================================================================================//

//                          LOCAL_FUNCTIONS_DECLARATION

//========================================================================================//

static sf::Color get_sphere_pixel_color(const CoordinateSus& cts, uint x_pix, uint y_pix);

static void draw_sphere(const CoordinateSus& cts, sf::Vertex* pixels);

/*
inline double graphic_function(double x){
    if(fabs(x) < EPS) return 0;
    return x / sin(x);
}
*/
//========================================================================================//

//                          PUBLIC_FUNCTIONS_DEFINITION

//========================================================================================//


// TODO:
/*
void DrawGraphic(sf::RenderWindow* window, CoordinateSus& ct_sus){

    Vector x_ax_vtor(ct_sus->x_upper_lim() - ct_sus->x_lower_lim(), 0, x_ax_start_point);
    Vector y_ax_vtor(0, ct_sus->y_upper_lim() - ct_sus->y_lower_lim(), y_ax_start_point);

    x_ax_vtor.Draw(window, ct_sus);
    y_ax_vtor.Draw(window, ct_sus);

    double step_val    = ct_sus->get_step_val();
    double x_lower_lim = ct_sus->x_lower_lim();
    double x_upper_lim = ct_sus->x_upper_lim();

    Point begin_point(x_lower_lim, Function(x_lower_lim));

    double y_last_val = Function(x_lower_lim + step_val);
    Vector last_vec(step_val, y_last_val - Function(x_lower_lim), begin_point);

    last_vec.Draw(window, ct_sus);

    for(double x_pos = x_lower_lim + step_val * 2; x_upper_lim - x_pos > -EPS; x_pos += step_val){
        
        double y_cur_val = Function(x_pos);
        Vector cur_vec(step_val, y_cur_val - y_last_val, &last_vec);

        cur_vec.Draw(window, ct_sus);
        last_vec   = cur_vec;
        y_last_val = y_cur_val;
    }
  
    return;
}
//----------------------------------------------------------------------------------------//
*/

void DrawSphere(){

    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "graphics");

    CoordinateSus cts(10, 710, 710, 10, -100, 100, -100, 100);

    uint n_y_pixels = cts.y_lower_pixel() - cts.y_upper_pixel() + 1;
    uint n_x_pixels = cts.x_upper_pixel() - cts.x_lower_pixel() + 1;
    
    sf::Vertex* pixels = new sf::Vertex[n_y_pixels * n_x_pixels];

    draw_sphere(&cts, pixels);

    while(window.isOpen()){

        sf::Event event;
		while (window.pollEvent(event)){
			if (event.type == sf::Event::Closed){
				window.close();
            }
		}

        window.clear(sf::Color::White);

        window.draw(pixels, n_x_pixels * n_y_pixels, sf::Points);

        window.display();
    }

    delete []pixels;

    return;
}
//----------------------------------------------------------------------------------------//

void draw_sphere(const CoordinateSus& cts, sf::Vertex* pixels){

    assert(pixels != NULL);

    uint n_pixel = 0;

    uint y_min = cts->y_upper_pixel();
    uint y_max = cts->y_lower_pixel();
    uint x_min = cts->x_lower_pixel();
    uint x_max = cts->x_upper_pixel();
    
    for(uint y_i = y_min; y_i <= y_max ; y_i++){
        for(uint x_i = x_min; x_i <= x_max; x_i++){
            
            sf::Color cur_color = get_sphere_pixel_color(cts, x_i, y_i);
            pixels[n_pixel++] = sf::Vertex(sf::Vector2f(x_i, y_i), cur_color);
        }
    }

    return;
}
//----------------------------------------------------------------------------------------//

static sf::Color get_sphere_pixel_color(const CoordinateSus& cts, uint x_pix, uint y_pix){

    double x_real = cts.CountAxisPosX(x_pix);
    double y_real = cts.CountAxisPosY(y_pix);
    
    double z_real_quad = SPHERE_RADIUS * SPHERE_RADIUS - x_real * x_real - y_real * y_real;
    if(z_real_quad <= EPS) return sf::Color::White;

    double z_real = sqrt(z_real_quad);

    Vector3D to_point_vtor(x_real, y_real, z_real);
    Vector3D light_to_point_vtor    = LIGHT_VTOR - pixel_vtor;
    Vector3D beholder_to_point_vtor = BEHOLDER_VTOR - pixel_vtor;
    
    double cosA = CountCosAngle(to_point_vtor, light_to_point_vtor);

    double diffuse_ratio  = 0;
    double specular_ratio = 0;

    if(cosA > EPS){
        diffuse_ratio = cosA;

        to_point_vtor.ChangeLen(cosA * light_to_point_vtor.len());
        
        Vector3D light_reflected_vtor = to_point_vtor * 2 - light_to_point_vtor;
        specular_ratio = CountCosAngle(light_reflected_vtor, beholder_to_point_vtor);
    }

    sf::Color col;

    col.r = LIGHT_COLOR.r * SPHERE_COLOR.r * diffuse_ratio * COLOR_DIV_RATIO * DIFFUSE_RATIO + 
            LIGHT_COLOR.r * SPHERE_COLOR.r * AMBIENT_RATIO * COLOR_DIV_RATIO * AMBIENT_RATIO + 
            LIGHT_COLOR.r * specular_ratio * SPECULAR_RATIO;
    
    col.g = LIGHT_COLOR.g * SPHERE_COLOR.g * diffuse_ratio * COLOR_DIV_RATIO * DIFFUSE_RATIO + 
            LIGHT_COLOR.g * SPHERE_COLOR.g * AMBIENT_RATIO * COLOR_DIV_RATIO * AMBIENT_RATIO + 
            LIGHT_COLOR.g * specular_ratio * SPECULAR_RATIO;

    col.b = LIGHT_COLOR.b * SPHERE_COLOR.b * diffuse_ratio * COLOR_DIV_RATIO * DIFFUSE_RATIO + 
            LIGHT_COLOR.b * SPHERE_COLOR.b * AMBIENT_RATIO * COLOR_DIV_RATIO * AMBIENT_RATIO + 
            LIGHT_COLOR.b * specular_ratio * SPECULAR_RATIO;

    col.b = LIGHT_COLOR.a * SPHERE_COLOR.a * diffuse_ratio * COLOR_DIV_RATIO * DIFFUSE_RATIO + 
            LIGHT_COLOR.a * SPHERE_COLOR.a * AMBIENT_RATIO * COLOR_DIV_RATIO * AMBIENT_RATIO + 
            LIGHT_COLOR.a * specular_ratio * SPECULAR_RATIO;

    return col;   
}
//----------------------------------------------------------------------------------------//

void BasicVectorActionsTest(){

    CoordinateSus cts1(10, 210, 210, 10, -10, 10, -10, 10);
    CoordinateSus cts2(240, 440, 440, 240, -10, 10, -10, 10);

    double cts1_ct_x = CTS1_CT_X_INIT, cts1_ct_y = CTS1_CT_Y_INIT;
    double cts2_ct_x = 0, cts2_ct_y = 0;

    clock_t init_time = clock();
    uint cur_sec_val  = 0;

    // TODO: add text
    myButton butt_reset(40, 490, 140, 540);
    myButton butt_exit(160, 490, 260, 540);

    while(window.isOpen()){

        sf::Event event;
		while (window.pollEvent(event)){
			if (event.type == sf::Event::Closed){
				window.close();
            }
            else if(event.type == sf::Event::MouseButtonPressed){

                int mouseX = event.mouseButton.x;
                int mouseY = event.mouseButton.y;
                
                if(mouseX < cts1.x_upper_pixel() && mouseX > cts1.x_lower_pixel() &&
                   mouseY < cts1.y_lower_pixel() && mouseY > cts1.y_upper_pixel()){

                    cts1_ct_x = cts1.CountAxisPosX(mouseX);
                    cts1_ct_y = cts1.CountAxisPosY(mouseY);
                }

                if(CheckCoordInButton(&butt_reset, mouseX, mouseY)){
                    cts1_ct_x = CTS1_CT_X_INIT;
                    cts1_ct_y = CTS1_CT_Y_INIT;
                }
                
                if(CheckCoordInButton(&butt_exit, mouseX, mouseY)){
                    window.close();
                }
            }
		}

        window.clear();
        butt_reset.Draw(&window);
        butt_exit.Draw(&window);

        cts1.Draw(&window);
        cts2.Draw(&window);

        if(clock() - init_time >= CLOCKS_PER_SEC){
            cur_sec_val = (cur_sec_val + (int)floor((clock() - init_time) / CLOCKS_PER_SEC)) % 60; 
            init_time   = clock();
        }


        double time_vtor_angle = M_PI / 2 - (2 * M_PI) / 60 * cur_sec_val;
        Vector code_time_vtor(TIME_VECTOR_LEN, time_vtor_angle, VT_DATA::POLAR);
        code_time_vtor.Draw(&window, &cts2);

        Vector click_vtor(cts1_ct_x, cts1_ct_y, VT_DATA::COORD);
        click_vtor.Draw(&window, &cts1);

        window.display();
    }

    return;
}
//----------------------------------------------------------------------------------------//

/*
        for(uint n_y_graphic = 0; n_y_graphic < N_Y_GRAPHS; n_y_graphic++){
            for(uint n_x_graphic = 0; n_x_graphic <  N_X_GRAPHS; n_x_graphic++){

            CoordinateSus ct_sus(n_x_graphic * N_X_SIZE, (n_x_graphic + 1) * N_X_SIZE,
                                    (n_y_graphic + 1) * N_Y_SIZE, n_y_graphic * N_Y_SIZE,
                                    -10, 10, -10, 10);
            DrawGraphic(&window, &ct_sus);                    
            }
        }
*/
//        DrawGraphic(&window, &ct_sus_big);
  //      DrawGraphic(&window, &ct_sus_mini);

/*