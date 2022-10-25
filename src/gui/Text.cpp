#include "Text.h"
#include <string.h>

#include <assert.h>

Text::Text(const char* data, uint font_size, const Color& col):
    font_size_(font_size), col_(col){
        strncpy(data_, data, sizeof(data_)/sizeof(char));
    }

//----------------------------------------------------------------------------------------//
