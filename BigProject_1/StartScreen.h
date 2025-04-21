#pragma once
#include <SDL.h>

class StartScreen {
public:
    StartScreen(SDL_Renderer* renderer);
    void render();

private:
    SDL_Renderer* renderer;
    SDL_Texture* texture;
    SDL_Rect rect;
};
