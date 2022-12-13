#include "TextureManager.h"
#include "logger.h"
#include <string.h>
#include <dlfcn.h>
#include <filesystem>

static const char DEFAULT_PACK_PATH[] = "textures/def/";

// TODO: refactor naming
static char TEXTURE_NAMES[N_TEXTURES][40] = {
    "button.png",
    "button_hovered.png",
    "slider_button.png",
    "slider_bg.png",
};

TexturePack_::TexturePack_(){
    if(!loadPack(DEFAULT_PACK_PATH)){
        EDLOG("unable to load default texture pack \"%s\"", DEFAULT_PACK_PATH);
    }
}

TexturePack_::TexturePack_(const std::string& path_to_textures){
    if(!loadPack(path_to_textures)){
        MDLOG("unable to load texture pack \"%s\", default pack would be loaded", path_to_textures);
        loadPack(DEFAULT_PACK_PATH);
    }
}

TexturePack_::~TexturePack_(){
    for(int n_texture = 0; n_texture < N_TEXTURES; n_texture++){
        delete textures_[n_texture];
    }
}

bool TexturePack_::loadPack(const std::string& path_to_textures){

    int n_found_files = 0;
    for(const auto& file : std::filesystem::directory_iterator(path_to_textures)) {
        if (file.is_directory()) {
            continue;
        }

        for(int n_texture = 0; n_texture < N_TEXTURES; n_texture++){
            if(strcmp(TEXTURE_NAMES[n_texture], file.path().c_str()) == 0) n_found_files++;
        }
    }

    if(n_found_files != N_TEXTURES){
        MDLOG("textures are missing in \"%s\"", path_to_textures);
        return false;
    }

    for(const auto& file : std::filesystem::directory_iterator(path_to_textures)) {
        if (file.is_directory()) {
            continue;
        }

        for(int n_texture = 0; n_texture < N_TEXTURES; n_texture++){
            if(strcmp(TEXTURE_NAMES[n_texture], file.path().c_str()) == 0){
                textures_[n_texture]->drawImage(file.path());
            }
        }
    }

    return true;
}

const DrawableArea* TexturePack_::getTexture(TEXTURE_IDENT ident){ return textures_[static_cast<int>(ident)]; }
