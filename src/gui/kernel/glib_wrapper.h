#ifndef GRAPHIC_LIB_WRAPPER_H
#define GRAPHIC_LIB_WRAPPER_H

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include <SFML/RenderTarget.hpp>

#include "Pixel.h"
#include "Color.h"

// TODO: make cpp

// TODO: rename
// TODO: remve copypaste

// TODO: написать проверки на out_of_range

class PixBuffer{
public:
    PixBuffer(uint width, uint height):
        buffer_(width, height){}

    uint width()  const { return buffer_.getSize().x; }
    uint height() const { return buffer_.getSize().y; }

    void drawText(uint x_pixel, uint y_pixel, const std::string& str, uint font_size, const Color& col){
        sf::Text text_obj(str.c_str(), font_, font_size);
        text_obj.setPosition(x_pixel, y_pixel);
        
        text_obj.setFillColor(convertLibColor(col));
        buffer_.draw(text_obj);
        return;
    }

    void drawLine(uint x_pix1, uint y_pix1, uint x_pix2, uint y_pix2, const Color& col){
        sf::Color sf_col = convertLibColor(col);

        sf::Vertex line_to_draw[] = {
            sf::Vertex(sf::Vector2f(x_pix1, height() - y_pix1), sf_col),
            sf::Vertex(sf::Vector2f(x_pix2, height() - y_pix2), sf_col)
        };

        buffer_.draw(line_to_draw, 2, sf::Lines);
        return;
    }

    void drawPixel(uint x_pix, uint y_pix, const Color& col){
        sf::Color sf_col = convertLibColor(col);
        sf::Vertex pix_to_draw(sf::Vector2f(x_pix, height() - y_pix), sf_col);

        buffer_.draw(&pix_to_draw, 1, sf::Points);
        return;
    }

    void drawPixels(const std::vector<Pixel>& pixels){

        uint n_pixels = pixels.size();
        sf::Vertex* pix_to_draw = new sf::Vertex[n_pixels];

        for(uint n_pix = 0; n_pix < n_pixels; n_pix++){
            pix_to_draw[n_pix] = sf::Vertex(sf::Vector2f(pixels[n_pix].x(), pixels[n_pix].y()), convertLibColor(pixels[n_pix].col()));
        }

        buffer_.draw(pix_to_draw, n_pixels, sf::Points);
        delete[] pix_to_draw;
        return;
    }
    
    friend class GraphicsSpace;
private:
    sf::RenderTexture buffer_;
};

class GraphicSpace{

public:
    GraphicSpace(uint width, uint height):
        GraphicSpaceKernelAbstract(width, height),
        window_(sf::VideoMode(width, height), "NO SIGNAL"),
        font_()
    {
        // TODO: refactor
        font_.loadFromFile("../fonts/arial.ttf");
    }

    void clear(const Color& col){
        window_.clear(convertLibColor(col));
        return;
    }

    void show(){
        window_.display();
        return;
    }

    void close(){
        window_.close();
        return;
    }

    bool isOpen(){
        return window_.isOpen();
    }

    bool extractEvent(Event** p_event){

        sf::Event sf_event;
        if(!window_.pollEvent(sf_event)) return false;

        //if(sf_event.type == sf::Event::Closed){
        //    *p_event = new CloseButtonPressedEvent();
        //}
        if(sf_event.type == sf::Event::MouseButtonPressed){
            *p_event = new MouseLClickEvent(sf_event.mouseButton.x, sf_event.mouseButton.y);
        }
        else if(sf_event.type == sf::Event::KeyPressed){
            *p_event = new KeyPressedEvent((KEY_TYPE)sf_event.key.code);
        }
        else return false;
        return true;
    }

    void drawText(uint x_pixel, uint y_pixel, const std::string& str, uint font_size, const Color& col) override{
        sf::Text text_obj(str.c_str(), font_, font_size);
        text_obj.setPosition(x_pixel, y_pixel);
        
        text_obj.setFillColor(convertLibColor(col));
        window_.draw(text_obj);
    }

    void drawLine(uint x_pix1, uint y_pix1, uint x_pix2, uint y_pix2, const Color& col){
        sf::Color sf_col = convertLibColor(col);

        sf::Vertex line_to_draw[] = {
            sf::Vertex(sf::Vector2f(x_pix1, height() - y_pix1), sf_col),
            sf::Vertex(sf::Vector2f(x_pix2, height() - y_pix2), sf_col)
        };

        window_.draw(line_to_draw, 2, sf::Lines);
        return;
    }

    void drawPixel(uint x_pix, uint y_pix, const Color& col){
        sf::Color sf_col = convertLibColor(col);
        sf::Vertex pix_to_draw(sf::Vector2f(x_pix, height() - y_pix), sf_col);

        window_.draw(&pix_to_draw, 1, sf::Points);
        return;
    }

    void drawPixels(const std::vector<Pixel>& pixels){

        uint n_pixels = pixels.size();
        sf::Vertex* pix_to_draw = new sf::Vertex[n_pixels];

        for(uint n_pix = 0; n_pix < n_pixels; n_pix++){
            pix_to_draw[n_pix] = sf::Vertex(sf::Vector2f(pixels[n_pix].x(), pixels[n_pix].y()), convertLibColor(pixels[n_pix].col()));
        }

        window_.draw(pix_to_draw, n_pixels, sf::Points);
        delete[] pix_to_draw;
        return;
    }

    void drawPixBuffer(const PixBuffer& obj){
        sf::Sprite tmp_spite(obj.buffer_.getTexture()); 
        window_.draw(tmp_sprite);

        return;
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

#endif // GRAPHIC_LIB_WRAPPER_H
