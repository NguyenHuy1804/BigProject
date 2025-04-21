#pragma once
#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <SDL.h>

class Background {
public:
    Background(SDL_Renderer* renderer);
    ~Background();

    void update();
    void render();

private:
    SDL_Renderer* renderer;
    SDL_Texture* texture;
    SDL_Rect rect1, rect2;
    float scrollSpeed;
};

#endif

