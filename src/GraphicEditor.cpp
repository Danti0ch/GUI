#include "graphic_lib_wrapper.h"
#include <assert.h>

const void* EVENT_FUNC_POISON = 0xDEADBEAF;

GraphicSpace::GraphicSpace(uint x_pixels, uint y_pixels){

    window_ = sf::RenderWindow(sf::VideoMode(x_pixels, y_pixels), "NO SIGNAL");    

    mouse_button_press_handler_ = EVENT_FUNC_POISON;
    close_button_press_handler_ = EVENT_FUNC_POISON;
    update_                     = EVENT_FUNC_POISON;
}
//----------------------------------------------------------------------------------------//

void GraphicSpace::Show(){

    window_.display();
    return;
}
//----------------------------------------------------------------------------------------//

void GraphicSpace::Close(){

    window_.close();
    return;
}
//----------------------------------------------------------------------------------------//

void Clear(Color col){

    window_.clear(sf::Color(col.r(), col.g(), col.b(), col.a()));
    return;
}
//----------------------------------------------------------------------------------------//

// TODO: другой путь обработки??
void GraphicSpace::HandleEvents(){

    while(window_.isOpen()){

        sf::Event event;

        while(window_.pollEvent(event)){

            if(event.type == sf::Event::Closed){
                if(close_button_press_handler_ != EVENT_FUNC_POISON){
                    close_button_press_handler_(this);
                    return;
                }
            }
            else if(event.type == sf::Event::MouseButtonPressed){
                if(mouse_button_press_handler_ != EVENT_FUNC_POISON){
                    close_button_press_handler_(this, event.mouseButton.x, event.mouseButton.y);
                }
            }
        }

        if(update_ != EVENT_FUNC_POISON) update()
    }

    return;
}   
//----------------------------------------------------------------------------------------//

// TODO: нормальная обработка ошибки
void GraphicSpace::DrawLine(uint x_pix1, uint y_pix1, uint x_pix2, uint y_pix2, const Color& col){

    sf::Color sf_col(col.r(), col.g(), col.b(), col.a());

    sf::Vertex line_to_draw[] = {
        sf::Vertex(sf::Vector2f(x_pix1, y_pix1), sf_col),
        sf::Vertex(sf::Vector2f(x_pix2, y_pix2), sf_col)
    };

    window_.draw(line_to_draw, 2, sf::Lines);

    return;
}
//----------------------------------------------------------------------------------------//

void GraphicSpace::DrawPixel(uint x_pix, uint y_pix, const Color& col){

    sf::Color  sf_col(col.r(), col.g(), col.b(), col.a());
    sf::Vertex pix_to_draw(sf::Vertex2f(x_pix, y_pix), sf_col);

    window_.draw(&pix_to_draw, 1, sf::Points);

    return;
}
//----------------------------------------------------------------------------------------//

void GraphicSpace::SetMouseButtonPressEvent(void* func(GraphicSpace* obj, int x_pos, int y_pos)){
    
    assert(func != NULL);

    mouse_button_press_handler_ = func;
    return;
}
//----------------------------------------------------------------------------------------//

void GraphicSpace::SetCloseButtonPressEvent(void* func(GraphicSpace* obj)){
    
    assert(func != NULL);

    close_button_press_handler_ = func;
    return;
}
//----------------------------------------------------------------------------------------//

void GraphicSpace::SetUpdateHandler(void* func(GraphicSpace* obj)){

    assert(func != NULL);

    update_ = func;
    return;
}
//----------------------------------------------------------------------------------------//

void GraphicSpace::Draw(const myButton& butt){

    if(sizeX() < butt.x_upper_pix()) return;
    if(sizeY() < butt.y_lower_pix()) return;

    uint n_y_pixels = (butt.y_lower_pix() - butt.y_upper_pix() + 1);
    uint n_x_pixels = (butt.x_upper_pix() - butt.x_lower_pix() + 1);

    sf::Vertex* pixels = new sf::Vertex[n_y_pixels * n_x_pixels];

    Color but_color = butt.col();
    sf::Color sf_col(but_color.r(), but_color.g(), but_color.b(), but_color.a());

    for(uint y_i = 0; y_i < n_y_pixels; y_i++){
        for(uint x_i = 0; x_i < n_x_pixels; x_i++){
            pixels[y_i * n_x_pixels + x_i] = sf::Vertex(sf::Vector2f(x_i + x_lower_pix_, y_i + y_upper_pix_), sf_col);
        }
    }

    window_.draw(pixels, n_x_pixels * n_y_pixels, sf::Points);
    
    delete [] pixels;

    //draw_frame(this);
    return;
}
//----------------------------------------------------------------------------------------//

//========================================================================================//

//                          LOCAL_FUNCTIONS_DEFINITION

//========================================================================================//
