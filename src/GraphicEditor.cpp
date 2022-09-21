#include "graphic_lib_wrapper.h"
#include <assert.h>

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Vertex.hpp>

GraphicSpace::GraphicSpace(uint x_pixels, uint y_pixels):
    window_(sf::VideoMode(x_pixels, y_pixels), "NO SIGNAL")
{}
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

void GraphicSpace::Clear(Color col){

    window_.clear(sf::Color(col.r(), col.g(), col.b(), col.a()));
    return;
}
//----------------------------------------------------------------------------------------//

// TODO: другой путь обработки??
void GraphicSpace::Init(){

    bool is_event = false;

    while(window_.isOpen()){

        sf::Event event;

        while(window_.pollEvent(event)){
            
            if(event.type == sf::Event::Closed){
                this->CloseButtonPressHandler();
                return;
            }
            else if(event.type == sf::Event::MouseButtonPressed){
                this->MouseButtonPressHandler(event.mouseButton.x, event.mouseButton.y);
            }
            else if(event.type == sf::Event::KeyPressed){
                this->KeyPressHandler((Key)event.key.code);
            }
            is_event = true;
        }

        if(is_event){
            this->UpdateAfterEvents();
            is_event = false;
        }

        this->Update();
    }

    return;
}   
//----------------------------------------------------------------------------------------//

void GraphicSpace::DrawLine(uint x_pix1, uint y_pix1, uint x_pix2, uint y_pix2, Color col){

    sf::Color sf_col(col.r(), col.g(), col.b(), col.a());

    sf::Vertex line_to_draw[] = {
        sf::Vertex(sf::Vector2f(x_pix1, y_pix1), sf_col),
        sf::Vertex(sf::Vector2f(x_pix2, y_pix2), sf_col)
    };

    window_.draw(line_to_draw, 2, sf::Lines);

    return;
}
//----------------------------------------------------------------------------------------//

void GraphicSpace::DrawPixel(uint x_pix, uint y_pix, Color col){

    sf::Color  sf_col(col.r(), col.g(), col.b(), col.a());

    // ???
    sf::Vertex pix_to_draw(sf::Vector2f(x_pix, sizeY() - y_pix), sf_col);

    window_.draw(&pix_to_draw, 1, sf::Points);

    return;
}
//----------------------------------------------------------------------------------------//

void GraphicSpace::Draw(const myButton& butt){

    uint x_lower_pix = butt.x_lower_pix();
    uint x_upper_pix = butt.x_upper_pix();
    uint y_lower_pix = butt.y_lower_pix();
    uint y_upper_pix = butt.y_upper_pix();
    
    if(sizeX() < x_upper_pix) return;
    if(sizeY() < y_lower_pix) return;

    uint n_y_pixels = (y_lower_pix - y_upper_pix + 1);
    uint n_x_pixels = (x_upper_pix - x_lower_pix + 1);

    sf::Vertex* pixels = new sf::Vertex[n_y_pixels * n_x_pixels];

    Color but_color = butt.col();
    sf::Color sf_col(but_color.r(), but_color.g(), but_color.b(), but_color.a());

    for(uint y_i = 0; y_i < n_y_pixels; y_i++){
        for(uint x_i = 0; x_i < n_x_pixels; x_i++){
            pixels[y_i * n_x_pixels + x_i] = sf::Vertex(sf::Vector2f(x_i + x_lower_pix, y_i + y_upper_pix), sf_col);
        }
    }

    window_.draw(pixels, n_x_pixels * n_y_pixels, sf::Points);

    delete [] pixels;

    //draw_frame(this);
    return;
}
//----------------------------------------------------------------------------------------//
