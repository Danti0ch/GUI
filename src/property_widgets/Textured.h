#ifndef TEXTURED_H
#define TEXTURED_H

#include "Widget.h"
#include "TextureManager.h"

class Textured : virtual public Widget{
public:
    Textured(TEXTURE_IDENT ident);
    Textured(Vector size);
    //~Textured();
};

#endif // TEXTURED_H
