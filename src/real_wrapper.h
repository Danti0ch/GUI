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

class GraphicSpaceKernel : public GraphicSpaceKernelAbstract{

    void drawText(drawText(uint x_pixel, uint y_pixel, const std::string& str, uint font_size, Color col) override{
        sf::Text text_obj(str.c_str(), font_, font_size);
        text_obj.setPosition(x_pixel, height() - y_pixel);

        text_obj.setFillColor(convertLibColor(col));

        window_.draw(text_obj);
    };

    void drawLine(uint x_pix1, uint y_pix1, uint x_pix2, uint y_pix2, Color col) override {
        sf::Color sf_col = convertLibColor(col);

        sf::Vertex line_to_draw[] = {
            sf::Vertex(sf::Vector2f(x_pix1, sizeY() - y_pix1), sf_col),
            sf::Vertex(sf::Vector2f(x_pix2, sizeY() - y_pix2), sf_col)
        };

        window_.draw(line_to_draw, 2, sf::Lines);
        return;
    }

    void drawPixel(uint x_pix, uint y_pix, Color col) override {
        sf::Color sf_col = convertLibColor(col);
        sf::Vertex pix_to_draw(sf::Vector2f(x_pix, sizeY() - y_pix), sf_col);

        window_.draw(&pix_to_draw, 1, sf::Points);
        return;
    }
    
private:
    sf::RenderWindow window_;

private:
    sf::Color convertLibColor(Color& col){
        sf::Color sf_col(col.r(), col.g(), col.b(), col.a());
        return sf_col;
    }
};

Matrix<Color> GetPixsFromFile(const std::string& filename){
    sf::Image img;
    if(!img.loadFromFile(filename)) return std::vector<Color>();

    uint n_x_pixels = img.getSize().x();
    uint n_y_pixels = img.getSize().y();
    
    Matrix<Color> storage(n_y_pixels, n_x_pixels);

    for(uint n_y = 0; n_y < n_y_pixels; n_y++){
        for(uint n_x = 0; n_x < n_x_pixels; n_x++){
            sf::Color col = img.getPixel();

            // TODO: create convert sf Color to color if there other sit like that
            storage.set(n_y, n_x, Color(col.r(), col.g(), col.b(), col.a()));
        }
    }
    return storage;
}
//----------------------------------------------------------------------------------------//

TRealWindow ConstructRealWindow(uint x_pixels)
#endif // GRAPHIC_LIB_WRAPPER_H
