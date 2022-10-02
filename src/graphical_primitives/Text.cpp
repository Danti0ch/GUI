#include "graphic_lib_wrapper.h"
#include <string.h>

#include <assert.h>

using namespace gglib;


Text::Text(const char* data, uint font_size, Color col):
    font_size_(font_size), col_(col){
        strncpy(data_, data, sizeof(data_)/sizeof(char));
    }

//----------------------------------------------------------------------------------------//

void Text::Draw(GraphicSpace* editor, uint x_pix, uint y_pix) const{

    assert(editor != NULL);

    // TODO: errors handling
    if(editor->sizeX() <= x_pix) return;
    if(editor->sizeY() <= y_pix) return;

    editor->DrawText(x_pix, y_pix, data_, font_size_, col_);
    return;
}

//----------------------------------------------------------------------------------------//
