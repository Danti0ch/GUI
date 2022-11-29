#ifndef GRAPHIC_LIB_WRAPPER_H
#define GRAPHIC_LIB_WRAPPER_H

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Vertex.hpp>

#include "Pixel.h"
#include "Color.h"
#include "Event.h"
#include "logger.h"
#include "tools.hpp"

#include <iostream>
// TODO: make cpp

// TODO: rename
// TODO: remve copypaste

// TODO: написать проверки на out_of_range

// FIXME: offset

// TODO: to namespace
class GraphicSpace;
class PixelBuffer;
class stImage;

class stImage : public booba::Image{
public:
    stImage(uint width, uint height):
    storage_(){
        storage_.create(width, height, convertLibColor(Color(255, 255, 255)));
    }
    
    virtual uint32_t getH() override{
        return storage_.getSize().y;
    }

    virtual uint32_t getX() override{
        return storage_.getSize().x;
    }

    void setX(uint x){ glob_x_ = x; }
    void setY(uint y){ glob_y_ = y; }

    uint x() const { return glob_x_; }
    uint y() const { return glob_y_; }
    
    virtual uint32_t getPixel(int32_t x, int32_t y) override{
        
        return static_cast<uint32_t>(convertFromLibColor(storage_.getPixel(x_coord(x), y_coord(y))));
    }

    virtual void putPixel(uint32_t x, uint32_t y, uint32_t color) override{
        storage_.setPixel(x_coord(x), y_coord(y), convertLibColor(Color(color)));
    }

    virtual uint32_t& operator()(uint32_t x, uint32_t y) override{
        return tmp;
    }

    virtual const uint32_t& operator()(uint32_t x, uint32_t y) const override{
        return tmp;
    }

    friend class PixelBuffer;
private:
    // TODO: rename
    sf::Image storage_;

    // TODO: fix
    uint tmp;

    uint glob_x_, glob_y_;
    sf::Color convertLibColor(const Color& col){
        sf::Color sf_col(col.r(), col.g(), col.b(), col.a());
        return sf_col;
    }

    Color convertFromLibColor(const sf::Color& sf_col){
        Color col(sf_col.r, sf_col.g, sf_col.b, sf_col.a);

        return col;
    }

    uint x_coord(uint val){
        return val;
    }

    uint y_coord(uint val){
        return getH() - val - 1;
    }
};

class PixelBuffer{
public:
    PixelBuffer(uint width, uint height):
        buffer_(),
        font_()
    {
        buffer_.create(width, height);
        font_.loadFromFile("../fonts/arial.ttf");
    }

    uint width()  const { return buffer_.getSize().x; }
    uint height() const { return buffer_.getSize().y; }

    void drawText(uint x_pixel, uint y_pixel, const std::string& str, uint font_size, const Color& col){
        sf::Text text_obj(str.c_str(), font_, font_size);
        
        text_obj.setPosition(x_coord(x_pixel), y_coord(y_pixel) - font_size);
        
        text_obj.setFillColor(convertLibColor(col));
        buffer_.draw(text_obj);
        return;
    }

    void drawLine(uint x_pix1, uint y_pix1, uint x_pix2, uint y_pix2, const Color& col){
        sf::Color sf_col = convertLibColor(col);

        sf::Vertex line_to_draw[] = {
            sf::Vertex(sf::Vector2f(x_coord(x_pix1), y_coord(y_pix1)), sf_col),
            sf::Vertex(sf::Vector2f(x_coord(x_pix2), y_coord(y_pix2)), sf_col)
        };

            buffer_.draw(line_to_draw, 2, sf::Lines);
        return;
    }

    void clear(const Color& col){
        buffer_.clear(convertLibColor(col));
        return;
    }

    void drawPixel(uint x_pix, uint y_pix, const Color& col){

        sf::Color sf_col = convertLibColor(col);
        sf::Vertex pix_to_draw(sf::Vector2f((x_pix), (y_pix)), sf_col);

        buffer_.draw(&pix_to_draw, 1, sf::Points);
        return;
    }
    
    void drawPixels(const std::vector<Pixel>& pixels){

        uint n_pixels = pixels.size();
        sf::Vertex* pix_to_draw = new sf::Vertex[n_pixels];

        for(uint n_pix = 0; n_pix < n_pixels; n_pix++){
            pix_to_draw[n_pix] = sf::Vertex(sf::Vector2f(x_coord(pixels[n_pix].x()), y_coord(pixels[n_pix].y())), convertLibColor(pixels[n_pix].col()));
        }

        buffer_.draw(pix_to_draw, n_pixels, sf::Points);
        delete[] pix_to_draw;

        buffer_.display();
        return;
    }
    
    void drawPixelBuffer(uint x, uint y, const PixelBuffer& obj){

        buffer_.display();
        sf::Sprite tmp_sprite(obj.buffer_.getTexture()); 
        tmp_sprite.setPosition(sf::Vector2f(x_coord(x), y_coord(y) - obj.height()));
        buffer_.draw(tmp_sprite);

        return;
    }

    void drawPixelBuffer(const PixelBuffer& obj, uint x_to, uint y_to, uint x_from, uint y_from, uint other_width, uint other_height){

        sf::Sprite tmp_sprite(obj.buffer_.getTexture(), sf::IntRect(obj.x_coord(x_from), obj.y_coord(y_from) - other_height, other_width, other_height)); 
        tmp_sprite.setPosition(sf::Vector2f(x_coord(x_to), y_coord(y_to) - other_height));
        
        buffer_.draw(tmp_sprite);

        return;
    }

    void draw(const stImage* img){

        sf::Texture tmp_texture;
        tmp_texture.loadFromImage(img->storage_);

        sf::Sprite tmp_sprite(tmp_texture); 

        buffer_.draw(tmp_sprite);
    }
private:
    sf::RenderTexture buffer_;
    sf::Font font_;
    
    friend class GraphicSpace;

    sf::Color convertLibColor(const Color& col){
        sf::Color sf_col(col.r(), col.g(), col.b(), col.a());
        return sf_col;
    }

    Color convertFromLibColor(const sf::Color& sf_col){
        Color col(sf_col.r, sf_col.g, sf_col.b, sf_col.a);

        return col;
    }

    //? fromLib ToLib?
    // TODO: make inline
    uint x_coord(uint val) const {
        return val;
    }

    uint y_coord(uint val) const{
        return height() - val;
    }
};

class GraphicSpace{

public:
    GraphicSpace(uint width, uint height):
        window_(sf::VideoMode(width, height), "NO SIGNAL"),
        font_(),
        mouse_data_(sf::Mouse::getPosition(window_).x, sf::Mouse::getPosition(window_).y, sf::Mouse::isButtonPressed(sf::Mouse::Left), sf::Mouse::isButtonPressed(sf::Mouse::Right)),
        special_keys_()
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

    uint width()  const { return window_.getSize().x; }
    uint height() const { return window_.getSize().y; }

    bool extractEvent(Event** p_event){

        sf::Event sf_event;
        if(!window_.pollEvent(sf_event)) return false;

        //if(sf_event.type == sf::Event::Closed){
        //    *p_event = new CloseButtonPressedEvent();
        //}

        if(sf_event.type == sf::Event::MouseButtonPressed || sf_event.type == sf::Event::MouseMoved || sf_event.type == sf::Event::MouseButtonReleased){
            
            mouse_data_.last_x_ = mouse_data_.x_;
            mouse_data_.last_y_ = mouse_data_.y_;
            
            if(sf_event.type ==  sf::Event::MouseMoved){
                mouse_data_.x_  = x_coord(sf_event.mouseMove.x);
                mouse_data_.y_  = y_coord(sf_event.mouseMove.y);
            }
            else{
                mouse_data_.x_  = x_coord(sf_event.mouseButton.x);
                mouse_data_.y_  = y_coord(sf_event.mouseButton.y);
            }

            if(sf_event.type == sf::Event::MouseButtonPressed){
                mouse_data_.isLPressed_ = true;
                *p_event = new MouseLClickEvent(mouse_data_, special_keys_);
            } 
            else if(sf_event.type == sf::Event::MouseMoved){
                // "Mouse moved: " << x_coord(sf_event.mouseButton.x) << " " << y_coord(sf_event.mouseButton.y) << " " << x_coord(sf_event.mouseMove.x) << " " << y_coord(sf_event.mouseMove.y) << "\n";
                *p_event = new MouseMovedEvent(mouse_data_, special_keys_);
            }
            else if(sf_event.type == sf::Event::MouseButtonReleased){
                mouse_data_.isRPressed_ = false;
                *p_event = new MouseReleasedEvent(mouse_data_, special_keys_);
            }
        }
        else if(sf_event.type == sf::Event::KeyPressed){
            *p_event = new KeyPressedEvent((T_KEY)sf_event.key.code);

            special_keys_.lShift_ = sf::Keyboard::isKeyPressed(sf::Keyboard::LShift);
            special_keys_.rShift_ = sf::Keyboard::isKeyPressed(sf::Keyboard::RShift);
            special_keys_.ctrl_   = sf::Keyboard::isKeyPressed(sf::Keyboard::LControl);
            special_keys_.alt_    = sf::Keyboard::isKeyPressed(sf::Keyboard::LAlt);
        }
        else return false;
        return true;
    }

    void drawText(uint x_pixel, uint y_pixel, const std::string& str, uint font_size, const Color& col){
        sf::Text text_obj(str.c_str(), font_, font_size);
        text_obj.setPosition(x_coord(x_pixel), y_coord(y_pixel));
        
        text_obj.setFillColor(convertLibColor(col));
        window_.draw(text_obj);
    }

    void drawLine(uint x_pix1, uint y_pix1, uint x_pix2, uint y_pix2, const Color& col){
        sf::Color sf_col = convertLibColor(col);

        sf::Vertex line_to_draw[] = {
            sf::Vertex(sf::Vector2f(x_coord(x_pix1), y_coord(y_pix1)), sf_col),
            sf::Vertex(sf::Vector2f(x_coord(x_pix2), y_coord(y_pix2)), sf_col)
        };

        window_.draw(line_to_draw, 2, sf::Lines);
        return;
    }

    void drawPixel(uint x_pix, uint y_pix, const Color& col){
        sf::Color sf_col = convertLibColor(col);
        sf::Vertex pix_to_draw(sf::Vector2f(x_coord(x_pix), y_coord(y_pix)), sf_col);
        
        window_.draw(&pix_to_draw, 1, sf::Points);
        return;
    }

    void drawPixels(const std::vector<Pixel>& pixels){

        uint n_pixels = pixels.size();
        sf::Vertex* pix_to_draw = new sf::Vertex[n_pixels];

        for(uint n_pix = 0; n_pix < n_pixels; n_pix++){
            pix_to_draw[n_pix] = sf::Vertex(sf::Vector2f(x_coord(pixels[n_pix].x()), y_coord(pixels[n_pix].y())), convertLibColor(pixels[n_pix].col()));
        }

        window_.draw(pix_to_draw, n_pixels, sf::Points);
        delete[] pix_to_draw;
        return;
    }

    void drawPixelBuffer(uint x, uint y, PixelBuffer& obj){

        window_.clear();

        sf::Sprite tmp_sprite(obj.buffer_.getTexture()); 
        window_.draw(tmp_sprite);

        return;
    }
private:
    sf::Color convertLibColor(const Color& col){
        sf::Color sf_col(col.r(), col.g(), col.b(), col.a());
        return sf_col;
    }

    uint x_coord(uint val) const {
        return val;
    }

    uint y_coord(uint val) const{
        return height() - val;
    }

private:
    sf::RenderWindow window_;
    sf::Font font_;

    //? static????
    MouseData mouse_data_;
    SpecialKeysData special_keys_;
};

#endif // GRAPHIC_LIB_WRAPPER_H
