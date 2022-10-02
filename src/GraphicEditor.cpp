#include "graphic_lib_wrapper.h"
#include <assert.h>

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Vertex.hpp>

using namespace gglib;

inline sf::Color convertColorToLib(Color col){
    sf::Color sf_col(col.r(), col.g(), col.b(), col.a());
    return sf_col;
}
//----------------------------------------------------------------------------------------//

GraphicSpace::GraphicSpace(uint x_pixels, uint y_pixels):
    window_(sf::VideoMode(x_pixels, y_pixels), "NO SIGNAL")
{
    font_.loadFromFile("../fonts/arial.ttf");
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

void GraphicSpace::Clear(Color col){

    window_.clear(convertColorToLib(col));
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
                this->MouseButtonPressHandler(event.mouseButton.x, sizeY() - event.mouseButton.y);
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

    sf::Color sf_col = convertColorToLib(col);

    sf::Vertex line_to_draw[] = {
        sf::Vertex(sf::Vector2f(x_pix1, sizeY() - y_pix1), sf_col),
        sf::Vertex(sf::Vector2f(x_pix2, sizeY() - y_pix2), sf_col)
    };

    window_.draw(line_to_draw, 2, sf::Lines);

    return;
}
//----------------------------------------------------------------------------------------//

void GraphicSpace::DrawPixel(uint x_pix, uint y_pix, Color col){

    sf::Color sf_col = convertColorToLib(col);

    sf::Vertex pix_to_draw(sf::Vector2f(x_pix, sizeY() - y_pix), sf_col);

    window_.draw(&pix_to_draw, 1, sf::Points);

    return;
}
//----------------------------------------------------------------------------------------//

void GraphicSpace::DrawText(uint x_pixel, uint y_pixel, const char* str, uint font_size, Color col){

    sf::Text text_obj(str, font_, font_size);
    text_obj.setPosition(x_pixel, sizeY() - y_pixel);

    text_obj.setFillColor(convertColorToLib(col));

    window_.draw(text_obj);

    return;
}
//----------------------------------------------------------------------------------------//
