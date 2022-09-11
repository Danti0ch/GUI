#ifndef GUI_H
#define GUI_H

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Vertex.hpp>

typedef unsigned int uint;

class myButton{

private:
    uint x_upper_pix_, x_lower_pix_;
    uint y_upper_pix_, y_lower_pix_;
public:

    myButton(uint x_lower_pix, uint y_upper_pix, uint x_upper_pix, uint y_lower_pix);

    uint x_lower_pix(){ return x_lower_pix_; }
    uint x_upper_pix(){ return x_upper_pix_; }
    uint y_lower_pix(){ return y_lower_pix_; }
    uint y_upper_pix(){ return y_upper_pix_; }
    
    void Draw(sf::RenderWindow* window);
};

int CheckCoordInButton(const myButton& but, uint x, uint y);

#endif //GUI_H
