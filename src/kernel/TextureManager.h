#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include <string>
#include <graphicImp.h>


//? to names
enum class TEXTURE_IDENT{
    BUTTON,
    BUTTON_HOVERED,
    H_SLIDER_BG,
    H_SLIDER_BUTTON,
    V_SLIDER_BG,
    V_SLIDER_BUTTON,
    N_TEXTURES
};

const unsigned int N_TEXTURES = static_cast<unsigned int>(TEXTURE_IDENT::N_TEXTURES);

class TexturePack_{
public:
    TexturePack_();
    TexturePack_(const std::string& path_to_textures);
    ~TexturePack_();

    /// @brief returns 1 if loading was successfull. 0 otherwise.
    bool loadPack(const std::string& path_to_textures);
    const DrawableArea* getTexture(TEXTURE_IDENT ident);
private:
    DrawableArea* textures_[N_TEXTURES];
};

TexturePack_ TexturePack;

#endif // TEXTURE_MANAGER_H
