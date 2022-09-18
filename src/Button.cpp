#include "graphic_lib_wrapper.h"
#include <assert.h>
#include <iostream>

myButton::myButton(uint x_lower_pix, uint y_upper_pix, uint x_upper_pix, uint y_lower_pix, Color col):
    x_upper_pix_(x_upper_pix),
    x_lower_pix_(x_lower_pix),
    y_upper_pix_(y_upper_pix),
    y_lower_pix_(y_lower_pix),
    col_(col)
{}
//----------------------------------------------------------------------------------------//

int CheckCoordInButton(const myButton& but, uint x, uint y){

    if(x < but.x_lower_pix() || x > but.x_upper_pix()) return 0;
    if(y < but.y_upper_pix() || y > but.y_lower_pix()) return 0;
    
    return 1;
}
//----------------------------------------------------------------------------------------//
