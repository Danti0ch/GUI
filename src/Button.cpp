#include "gui.h"
#include <assert.h>
#include <iostream>

myButton::myButton(uint x_lower_pix, uint y_upper_pix, uint x_upper_pix, uint y_lower_pix, gl::Color col):
    x_upper_pix_(x_upper_pix),
    x_lower_pix_(x_lower_pix),
    y_upper_pix_(y_upper_pix),
    y_lower_pix_(y_lower_pix),
    col_(col)
{}
//----------------------------------------------------------------------------------------//

void myButton::Draw(gk::Window* window){

    assert(window != NULL);    

    if(GetWindowXSize(*window) < x_upper_pix_) return;
    if(window->getSize().y < y_lower_pix_) return;

    uint n_y_pixels = (y_lower_pix_ - y_upper_pix_ + 1);
    uint n_x_pixels = (x_upper_pix_ - x_lower_pix_ + 1);
    
    for(uint y_i = 0; y_i < n_y_pixels; y_i++){
        for(uint x_i = 0; x_i < n_x_pixels; x_i++){
            DrawPixel(x_i + x_lower_pix_, y_i + y_upper_pix_, col_);
        }
    }

    //draw_frame(this);
    return;
}
//----------------------------------------------------------------------------------------//

int CheckCoordInButton(const myButton& but, uint x, uint y){

    if(x < but.x_lower_pix() || x > but.x_upper_pix()) return 0;
    if(y < but.y_upper_pix() || y > but.y_lower_pix()) return 0;
    
    return 1;
}
//----------------------------------------------------------------------------------------//
