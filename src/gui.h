#ifndef GUI_H
#define GUI_H

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Vertex.hpp>

typedef unsigned int uint;

class myButton{

private:
    uint x_upper_pix_, x_lower_pix_;
    uint y_upper_pix_, y_lower_pix_;

    sf::Color col_;

public:

    myButton(uint x_lower_pix, uint y_upper_pix, uint x_upper_pix, uint y_lower_pix, sf::Color col = sf::Color::Black);

    uint x_lower_pix() const { return x_lower_pix_; }
    uint x_upper_pix() const { return x_upper_pix_; }
    uint y_lower_pix() const { return y_lower_pix_; }
    uint y_upper_pix() const { return y_upper_pix_; }
    
    void Draw(sf::RenderWindow* window);
};

void DrawLine(sf::RenderWindow* window, double x1, double y1, double x2, double y2, sf::Color col = sf::Color::White);
int  CheckCoordInButton(const myButton& but, uint x, uint y);

#endif //GUI_H
