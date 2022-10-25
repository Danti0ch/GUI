#ifndef GRAPHIC_LIB_WRAPPER_H
#define GRAPHIC_LIB_WRAPPER_H

/*
#define SFML_LIB 0
#define QT_LIB   1

#ifndef ACTIVE_GRAPHIC_LIB
#define ACTIVE_GRAPHIC_LIB SFML_LIB
#endif
*/

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include "GraphicSpaceKernelAbstract.h"
#include <iostream>

class GraphicSpace : public GraphicSpaceKernelAbstract{

public:
    GraphicSpace(uint width, uint height):
        GraphicSpaceKernelAbstract(width, height),
        window_(sf::VideoMode(width, height), "NO SIGNAL"),
        font_()
    {
        font_.loadFromFile("../fonts/arial.ttf");
    }

    void drawText(uint x_pixel, uint y_pixel, const std::string& str, uint font_size, Color col) override{
        sf::Text text_obj(str.c_str(), font_, font_size);
        text_obj.setPosition(x_pixel, height() - y_pixel);

        text_obj.setFillColor(convertLibColor(col));

        window_.draw(text_obj);
    }

    void drawLine(uint x_pix1, uint y_pix1, uint x_pix2, uint y_pix2, Color col) override {
        sf::Color sf_col = convertLibColor(col);

        sf::Vertex line_to_draw[] = {
            sf::Vertex(sf::Vector2f(x_pix1, height() - y_pix1), sf_col),
            sf::Vertex(sf::Vector2f(x_pix2, height() - y_pix2), sf_col)
        };

        window_.draw(line_to_draw, 2, sf::Lines);
        return;
    }

    void drawPixel(uint x_pix, uint y_pix, Color col) override {
        sf::Color sf_col = convertLibColor(col);
        sf::Vertex pix_to_draw(sf::Vector2f(x_pix, height() - y_pix), sf_col);

        window_.draw(&pix_to_draw, 1, sf::Points);
        return;
    }
    
    void drawPixels(const std::vector<Pixel>& pixels) override {

        uint n_pixels = pixels.size();
        sf::Vertex* pix_to_draw = new sf::Vertex[n_pixels];

        for(uint n_pix = 0; n_pix < n_pixels; n_pix++){
            pix_to_draw[n_pix] = sf::Vertex(sf::Vector2f(pixels[n_pix].x(), pixels[n_pix].y()), convertLibColor(pixels[n_pix].col()));
        }

        window_.draw(pix_to_draw, n_pixels, sf::Points);
        delete[] pix_to_draw;
        return;
    }

    void clear(Color col) override{
        window_.clear(convertLibColor(col));
        return;
    }

    void show() override{
        window_.display();
        return;
    }

    void close() override{
        window_.close();
        return;
    }

    bool isopen() override{
        return window_.isOpen();
    }

    bool extractEvent(CoreEvent* core_event) override {
        sf::Event sf_event;
        if(!window_.pollEvent(sf_event)) return false;

        /*
        if(sf_event.type == sf::Event::Closed){
            *event = Event(EVENT_TYPE::CLOSE_BUTTON_PRESSED);
            return true;
        }*/
        if(sf_event.type == sf::Event::MouseButtonPressed){

            // TODO: refactor this            
            free(CoreEvent);
            *CoreEvent = new MouseLClickCoreEvent(width() - sf_event.mouseButton.x, height() - sf_event.mouseButton.y);
            return true;
        }
        else if(sf_event.type == sf::Event::KeyPressed){

            free(CoreEvent);
            *CoreEvent = new KeyPressedCoreEvent((KEY_TYPE)sf_event.key.code);
            return true;
        }

        return false;
    }

private:
    sf::RenderWindow window_;
    sf::Font font_;

private:
    sf::Color convertLibColor(const Color& col){
        sf::Color sf_col(col.r(), col.g(), col.b(), col.a());
        return sf_col;
    }
};

//----------------------------------------------------------------------------------------//
/*
Matrix<Color> GetPixsFromFile(const std::string& filename){
    sf::Image img;
    if(!img.loadFromFile(filename)) return Matrix<Color>(0, 0);

    uint n_x_pixels = img.getSize().x;
    uint n_y_pixels = img.getSize().y;
    
    Matrix<Color> storage(n_y_pixels, n_x_pixels);

    for(uint n_y = 0; n_y < n_y_pixels; n_y++){
        for(uint n_x = 0; n_x < n_x_pixels; n_x++){
            sf::Color col = img.getPixel(n_x, n_y);

            // TODO: create convert sf Color to color if there other sit like that
            storage.set(n_y, n_x, Color(col.r, col.g, col.b, col.a));
        }
    }
    return storage;
}
*/
#endif // GRAPHIC_LIB_WRAPPER_H