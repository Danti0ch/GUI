#include "Textured.h"

Textured::Textured(TEXTURE_IDENT ident):
    Widget(TexturePack.getTexture(ident)->size())
{
    *bgLayer_ = *TexturePack.getTexture(ident);
}

Textured::Textured(Vector size):
    Widget(size)
{}
