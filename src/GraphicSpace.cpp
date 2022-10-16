#include "graphic_lib_wrapper.h"
#include <assert.h>

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Vertex.hpp>

using namespace gglib;

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

EVENT_TYPE GraphicSpace::extract_event_type(){

}
//----------------------------------------------------------------------------------------//

bool GraphicSpace::ExtractEvent(Event* p_event){
    sf::Event event;
    if(!window_.pollEvent(event)) return false;

    EVENT_TYPE type = get_event_type(event);

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
}
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
