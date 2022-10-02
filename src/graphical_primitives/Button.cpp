#include "graphic_lib_wrapper.h"
#include <assert.h>
#include <iostream>
#include <string.h>

using namespace gglib;

int BUTTON_TEXT_OFFSET_X = 15;
int BUTTON_TEXT_OFFSET_Y = 40;

Button::Button(uint x_lower_pix, uint y_lower_pix, uint x_upper_pix, uint y_upper_pix, const Text& str, Color col):
    x_upper_pix_(x_upper_pix),
    x_lower_pix_(x_lower_pix),
    y_upper_pix_(y_upper_pix),
    y_lower_pix_(y_lower_pix),
    text_(str),
    col_(col)
{}
//----------------------------------------------------------------------------------------//

void Button::Draw(GraphicSpace* editor){

    if(editor->sizeX() < x_lower_pix_) return;
    if(editor->sizeY() < y_lower_pix_) return;

    uint n_y_pixels = (y_upper_pix_ - y_lower_pix_ + 1);
    uint n_x_pixels = (x_upper_pix_ - x_lower_pix_ + 1);

    Color but_color = col();

    for(uint y_i = 0; y_i < n_y_pixels; y_i++){
        for(uint x_i = 0; x_i < n_x_pixels; x_i++){
            editor->DrawPixel(x_lower_pix_ + x_i, y_lower_pix_ + y_i, but_color);
        }
    }

    text_.Draw(editor, x_lower_pix_ + BUTTON_TEXT_OFFSET_X, y_lower_pix_ + BUTTON_TEXT_OFFSET_Y);

    return;
}
//----------------------------------------------------------------------------------------//


int gglib::CheckCoordInButton(const Button& but, uint x, uint y){

    if(x < but.x_upper_pix() && x > but.x_lower_pix() &&
       y < but.y_upper_pix() && y > but.y_lower_pix()){
        return 1;
    }
    return 0;
}
//----------------------------------------------------------------------------------------//
