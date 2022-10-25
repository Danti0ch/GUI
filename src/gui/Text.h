#ifndef TEXT_H
#define TEXT_H

#include <stdlib.h>
#include "Color.h"

class Text{
private:

    uint        font_size_;
    char        data_[64];
    Color       col_;
public:
    Text(const char* data, uint font_size, const Color& col);
    
    Color col() const { return col_; }
};
//----------------------------------------------------------------------------------------//

#endif // TEXT_H
