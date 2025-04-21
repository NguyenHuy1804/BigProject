#include "TextureManager.h"

SDL_Texture* TextureManager::LoadTexture(const std::string& file, SDL_Renderer* ren) {
    SDL_Surface* tmpSurface = IMG_Load(file.c_str());
    SDL_Texture* tex = SDL_CreateTextureFromSurface(ren, tmpSurface);
    SDL_FreeSurface(tmpSurface);
    return tex;
}
