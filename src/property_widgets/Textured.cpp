#include "Textured.h"

Textured::Textured(TEXTURE_IDENT ident):
    Widget(TexturePack::activePack.getTexture(ident)->size())
{
    //*bgLayer_ = *TexturePack::activePack.getTexture(ident);
}

Textured::Textured(Vector size):
    Widget(size)
{}
