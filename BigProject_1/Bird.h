#pragma once
#include <SDL.h>

class Bird {
public:
    Bird(SDL_Renderer* renderer);
    void update();
    void render();
    void flap();
    SDL_Rect getRect();

private:
    SDL_Renderer* renderer;
    SDL_Texture* texture;
    SDL_Rect rect;
    float velocity;
};
